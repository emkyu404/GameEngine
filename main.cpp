#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <string>

#include <iostream>
#include <vector>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "LoadShader.h"

// Inclut GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform.hpp>

//Utilities class
#include "Shader.h"
#include "Quaternion.h"

// Moteur
#include <Particle.hpp>

//Shapes
#include "Cube.h"
#include "Grid.h"
#include "Triangle.h"

//PhysicWorld
#include "PhysicWorld.h"

//Forces
#include "ParticleGravity.h"
#include "ParticleDrag.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleBuoyancy.h"

//Camera
#include "Camera.h"
#include <Matrix33.h>

#define MAX_NUMBER_PARTICLES 1000

using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static GLFWwindow* window; //GLFW window context

static GLuint MatrixID;
static Shape* particleShape;
static Shape* grid;

static Shader* particleShader;

static mat4 view,projection ,mvp, model;

static PhysicWorld physicWorld = PhysicWorld();
static int particleCount = 2;
static Vector3D offsetParticle = Vector3D(3, 0, 0); 

// Forces
static ParticleForceGenerator* gravity = new ParticleGravity(); // Gravity force is common to every particle
static ParticleForceGenerator* drag = new ParticleDrag(); 
//static ParticleForceGenerator* spring = new ParticleSpring();
//static ParticleForceGenerator* anchoredSpring = new ParticleAnchoredSpring();
static ParticleForceGenerator* buoyancy = new ParticleBuoyancy();

int detectorNumberParticle = 0; 

//time logic
float dt = 0.0f; //deltaTime
float lastFrame = 0.0f;
bool firstMouse = true;

//mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

Camera camera = Camera(10.0f, 3.0f, 10.0f);
static float camSpeed = 2.5f;

const static GLuint vao, vbo, ibo;

void initGL();
void paintGL();
void initParticles();
void setupImGUI(GLFWwindow* window, const char* glsl_version);
void renderImGUIMainFrame();
void initProjectionMatrix();
void mainLoop();
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void testMatrix();

int main()
{
	testMatrix();

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	/* Code from ImGUI example */
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Open OpenGL Window and create context
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialise GLEW
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Enable GL functions
	glEnable(GL_DEPTH_TEST);

	// Make sure we can capture keys
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);


	setupImGUI(window, glsl_version); // Setup ImGUI

	initGL(); // Initialize shapes to be rendered

	initProjectionMatrix(); // Initialize projection matrix

	initParticles();

	mainLoop(); // Main render loop

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void initGL() {
	// Chargement des shaders
	particleShader = new Shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");

	//VAO creation
	VAO* particleVao = new VAO();
	VAO* gridVao = new VAO();


	//Chargement OpenGL
	particleShape = new Cube(particleVao);
	particleShape->init();

	grid = new Grid(gridVao);
	grid->init();
}

void paintGL() {
	//Clear screen
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.getViewMatrix();
	
	
	for (Particle* particle : PhysicWorld::getInstance()->getParticles())
	{
		model = glm::translate(glm::vec3(particle->getPosition().getX(), particle->getPosition().getY(), particle->getPosition().getZ()));
		mvp = projection * view * model;
		// Précision du shader à utiliser
		particleShader->activate();

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		GLint color_location = glGetUniformLocation(particleShader->programID, "my_color");
		float color[3] = { 1.0f, 0.8f, 0.2f };
		glUniform3fv(color_location, 1, color);

		//grid->draw();
		//Color test
		particleShape->draw();
	}
}

void initParticles() 
{
	for (int i = 0; i < particleCount; ++i)
	{
		PhysicWorld::getInstance()->addParticle(Vector3D() + Vector3D(3 * i, 0, 0));
	}
}

void setupImGUI(GLFWwindow* window, const char* glsl_version) {
	/* ImGUI setup - From imGUI example code */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void rendererImGUICamera()
{
	ImGui::Begin("Camera"); 

	
	
	ImGui::SliderFloat("Movement speed", &camSpeed, 1.0f, 25.0f); 

	if (ImGui::Button("Set movement speed"))
	{
		camera.setMovementSpeed(camSpeed); 
	}

	ImGui::End(); 
}

bool VectorOfStringGetter(void* data, int n, const char** out_text)
{
	const vector<Vector3D>* particles = (vector<Vector3D>*)data;
	detectorNumberParticle++; 
	string text = "Particle " + to_string(detectorNumberParticle);
	//printf("%s", text); 
	*out_text = "Particle"; 

	return true;
}

void renderImGUIParticlesList()
{
	ImGui::Begin("Particles");

	PhysicWorld* instance = PhysicWorld::getInstance();
	float particleIndex = 0.0f; 
	int numberParticles = instance->getNumberOfParticles(); 

	for (Particle* particle : PhysicWorld::getInstance()->getParticles())
	{
		particleIndex++;
		ImGui::Text("Particle %.0f", particleIndex); 

		// Declare string names with ID to make sure GUI is ok with the buttons
		string text_customization_particle = std::string("Customization particle##") + std::to_string(particleIndex);
		string text_mass = std::string("Set inverse mass##") + std::to_string(particleIndex);
		string text_gravity = std::string("Apply Gravity##") + std::to_string(particleIndex);
		string text_drag = std::string("Apply Drag##") + std::to_string(particleIndex);
		string text_buoyancy = std::string("Apply Buoyancy##") + std::to_string(particleIndex);
		string text_spring = std::string("Apply Spring##") + std::to_string(particleIndex);
		string text_remove = std::string("Remove Particle##") + std::to_string(particleIndex);
		string text_particleList = std::string("Particle List##") + std::to_string(particleIndex);

		if (ImGui::CollapsingHeader(text_customization_particle.c_str()))
		{
			Vector3D position = particle->getPosition(); 
			Vector3D velocity = particle->getVelocity(); 
			Vector3D acceleration = particle->getAcceleration(); 

			ImGui::Text("Position : (%.1f, %.1f, %.1f)", position.getX(), position.getY(), position.getZ()); 
			ImGui::Text("Velocity : (%.1f, %.1f, %.1f)", velocity.getX(), velocity.getY(), velocity.getZ());
			ImGui::Text("Acceleration : (%.1f, %.1f, %.1f)", acceleration.getX(), acceleration.getY(), acceleration.getZ());

			//if (ImGui::Button(text_mass.c_str()))
			//{
			//	printf("%f", particle->GetInverseMass());
			//}

			if (ImGui::Button(text_gravity.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(particle, gravity);
			}

			if (ImGui::Button(text_drag.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(particle, drag);
			}

			if (ImGui::Button(text_buoyancy.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(particle, buoyancy);
			}


			static int selectedParticleSpring = 0;

			vector<Particle*> particlesVector = PhysicWorld::getInstance()->getParticles();
			particlesVector.erase(remove_if(particlesVector.begin(), particlesVector.end(), [&](const Particle* p) { return p == particle; }), particlesVector.end());;
			const char* out_text[MAX_NUMBER_PARTICLES];

			ImGui::Combo(text_particleList.c_str(), &selectedParticleSpring, *VectorOfStringGetter,
				(void *) &particlesVector, particlesVector.size());

			detectorNumberParticle = 0; 

			if (ImGui::Button(text_spring.c_str()))
			{
				ParticleForceGenerator* spring = new ParticleSpring(particlesVector[selectedParticleSpring]);
				PhysicWorld::getInstance()->addForceEntry(particle, spring);
			}

			if (ImGui::Button(text_remove.c_str()))
			{
				PhysicWorld::getInstance()->removeParticle(particle);
			}
		}
	}

	ImGui::End();
}



void renderImGUIMainFrame() {
	
	PhysicWorld* instance = PhysicWorld::getInstance();
	ImGui::Begin("Engine");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


	if (ImGui::Button("Add Particle"))
	{
		instance->addParticle(offsetParticle * instance->getNumberOfParticles());
	}

	if (ImGui::Button("Apply Gravity"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->addForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Disable Gravity"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->removeForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Apply Drag"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->addForceEntry(particle, drag);
		}
	}

	if (ImGui::Button("Disable Drag"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->removeForceEntry(particle, drag);
		}
	}

	if (ImGui::Button("Apply Buoyancy"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->addForceEntry(particle, buoyancy);
		}
	}

	if (ImGui::Button("Disable Buoyancy"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->removeForceEntry(particle, buoyancy);
		}
	}


	if (ImGui::Button("Remove all particles"))
	{
		for (Particle* particle : instance->getParticles())
		{
			instance->removeParticle(particle);
		}
	}

	if (ImGui::Button("Reset"))
	{
		for (Particle* particle : instance->getParticles())
		{
			particle->reset();
		}
	}

	ImGui::End();
}

void renderImGUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	renderImGUIMainFrame();
	renderImGUIParticlesList();
	rendererImGUICamera(); 
	ImGui::Render();
}

void initProjectionMatrix() {
	/* -- Matrice de projection -- */
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	view = glm::lookAt(
		vec3(10, 3, 10), // Camera is at (4,3,3), in World Space
		vec3(0, 0, 0), // and looks at the origin
		vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	//View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	// Model matrix : an identity matrix (model will be at the origin)
	model = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = projection * view * model; // Remember, matrix multiplication is the other way around

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	MatrixID = glGetUniformLocation(particleShader->programID, "MVP");
}

void mainLoop() {
	do {

		glfwPollEvents();

		//dt = ImGui::GetIO().DeltaTime; //dt => DeltaTime

		float currentFrame = static_cast<float>(glfwGetTime());
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window); // process all input

		// Update logic with our Vector3D class
		PhysicWorld::getInstance()->runPhysics(dt);

		renderImGUI(); //Create the ImGUI Frame
		// Clear and setup viewport
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		

		paintGL();

		// Real draw for ImGui in foreground 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


	} // Check if escape is pressed to close the window
	while (!glfwWindowShouldClose(window));
}

void processInput(GLFWwindow* _window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processKeyboard(FORWARD, dt);
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboard(BACKWARD, dt);
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processKeyboard(LEFT, dt);
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboard(RIGHT, dt);
	}
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.setLock(!camera.getLock());
	}
}

void mouseCallback(GLFWwindow* _window, double _xposIn, double _yposIn)
{
	float xpos = static_cast<float>(_xposIn);
	float ypos = static_cast<float>(_yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset, true);
}

void scrollCallback(GLFWwindow* window, double _xOffset, double _yOffset)
{
	camera.processMouseScroll(static_cast<float>(_yOffset));
}

void testMatrix() {
	float valuesM1[9] = {0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f};
	Matrix33 m1 = Matrix33(valuesM1);
	Matrix33 m2 = Matrix33();

	m1.printMatrix33();
	m1.getInverse().printMatrix33();
	m1.getTranspose().printMatrix33();

}
