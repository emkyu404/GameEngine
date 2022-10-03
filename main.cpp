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

// Moteur
#include <Particle.hpp>

//Shapes
#include "shapes/Triangle.h"

//PhysicWorld
#include "PhysicWorld.h"

//Forces
#include "ParticleGravity.h"
#include "ParticleDrag.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleBuoyancy.h"

using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static GLFWwindow* window; //GLFW window context

static GLuint m_triangleProgramID, MatrixID;
static Triangle triangle;

static mat4 View,Projection ,mvp, Model;

static PhysicWorld physicWorld = PhysicWorld();
static ParticleForceGenerator* gravity = new ParticleGravity(); // Gravity force is common to every particle
static ParticleForceGenerator* drag = new ParticleDrag(); 
//static ParticleForceGenerator* spring = new ParticleSpring();
//static ParticleForceGenerator* anchoredSpring = new ParticleAnchoredSpring();
static ParticleForceGenerator* buoyancy = new ParticleBuoyancy();

static int particleCount = 1;

void initGL();
void paintGL();
void spawnParticles(int numberOfParticle);
void setupImGUI(GLFWwindow* window, const char* glsl_version);
void renderImGUIFrame();
void initProjectionMatrix();
void mainLoop();

int main()
{
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

	setupImGUI(window, glsl_version); // Setup ImGUI

	initGL(); // Initialize shapes to be rendered

	initProjectionMatrix(); // Initialize projection matrix

	Particle p = Particle();
	p.SetMass(1);
	PhysicWorld::getInstance()->AddParticle(&p);

	Particle p2 = Particle();
	p2.SetMass(3);
	PhysicWorld::getInstance()->AddParticle(&p2);

	Particle p3 = Particle();
	p3.SetMass(4);
	PhysicWorld::getInstance()->AddParticle(&p3);

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
	m_triangleProgramID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(m_triangleProgramID, "vertexPosition_modelspace");

	//Chargement OpenGL
	triangle.init(vertexPosition_modelspaceID);
}

void paintGL() {
	// Précision du shader à utiliser
	glUseProgram(m_triangleProgramID);

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	triangle.draw();
}

void spawnParticles(int numberOfParticle) {
	for (int i = 0; i < numberOfParticle; i++)
	{
		Particle p = Particle(Vector3D((-numberOfParticle + i + 3.0f) * 2.5f, 0.0f, 0.0f));
		p.SetMass(1);
		PhysicWorld::getInstance()->AddParticle(&p);
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

void rendererImGUIParticlesList()
{
	ImGui::ShowDemoWindow(); 

	ImGui::Begin("Particles");

	float particleIndex = 0.0f; 

	for (Particle* particle : PhysicWorld::getInstance()->getParticles())
	{
		particleIndex++;
		ImGui::Text("Particle %.0f", particleIndex); 

		string text_mass = std::string("Set inverse mass##") + std::to_string(particleIndex);
		string text_gravity = std::string("Apply Gravity##") + std::to_string(particleIndex);
		string text_drag = std::string("Apply Drag##") + std::to_string(particleIndex);
		string text_buoyancy = std::string("Apply Buoyancy##") + std::to_string(particleIndex);

		if (ImGui::CollapsingHeader("Customization particle"))
		{
			Vector3D position = particle->GetPosition(); 
			Vector3D velocity = particle->GetAcceleration(); 
			Vector3D acceleration = particle->GetAcceleration(); 

			ImGui::Text("Position : (%.1f, %.1f, %.1f)", position.getX(), position.getY(), position.getZ()); 
			ImGui::Text("Velocity : (%.1f, %.1f, %.1f)", velocity.getX(), velocity.getY(), velocity.getZ());
			ImGui::Text("Acceleration : (%.1f, %.1f, %.1f)", acceleration.getX(), acceleration.getY(), acceleration.getZ());

			if (ImGui::Button(text_mass.c_str()))
			{
				printf("%f", particle->GetInverseMass());
			}

			if (ImGui::Button(text_gravity.c_str()))
			{
				PhysicWorld::getInstance()->AddForceEntry(particle, gravity);
			}

			if (ImGui::Button(text_drag.c_str()))
			{
				PhysicWorld::getInstance()->AddForceEntry(particle, drag);
			}

			if (ImGui::Button(text_buoyancy.c_str()))
			{
				PhysicWorld::getInstance()->AddForceEntry(particle, buoyancy);
			}
		}
	}

	ImGui::End();
}

void renderImGUIFrame() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Engine");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	/*
	ImGui::Checkbox("enable Gravity", &gravityEnabled);
	ImGui::DragFloat("Gravity", &gravity, 0.1f, -10.f, 10.f);

	ImGui::Checkbox("Other force enbale", &otherForceEnabled);
	ImGui::DragFloat3("Other force", (float*)(&otherForce), 0.1f, -10.f, 10.f);
	*/

	if (ImGui::Button("Apply Gravity particle"))
	{
		for (Particle* particle : PhysicWorld::getInstance()->getParticles())
		{
			PhysicWorld::getInstance()->AddForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Disable Gravity particle"))
	{
		for (Particle* particle : PhysicWorld::getInstance()->getParticles())
		{

			// Clear Velocity and Acceleration
			particle->SetAcceleration(Vector3D());
			particle->SetVelocity(Vector3D());

			PhysicWorld::getInstance()->RemoveForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Reset"))
	{
		for (Particle* particle : PhysicWorld::getInstance()->getParticles())
		{
			particle->Reset();
		}
	}

	/* TO CHANGE 
	if (ImGui::Button("Add Particle") && particleCount < 10)
	{
		particleCount++;
		//TODO handle offset
		Particle p = Particle(Vector3D((PhysicWorld::getInstance()->numberOfParticles() + 3.0f) * 2.5f, 0.0f, 0.0f));
		p.SetMass(1);
		PhysicWorld::getInstance()->addParticle(p);
	}

	if (ImGui::Button("RemoveParticle") && particleCount > 1) 
	{
		particleCount--;
		PhysicWorld::getInstance()->removeParticle();
	}
	*/

	ImGui::End();

	rendererImGUIParticlesList(); 


	ImGui::Render();
}

void initProjectionMatrix() {
	/* -- Matrice de projection -- */
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	View = glm::lookAt(
		vec3(10, 3, 10), // Camera is at (4,3,3), in World Space
		vec3(0, 0, 0), // and looks at the origin
		vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	MatrixID = glGetUniformLocation(m_triangleProgramID, "MVP");
}

void mainLoop() {
	do {

		glfwPollEvents();

		// Clear and setup viewport
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float dt = ImGui::GetIO().DeltaTime; //dt => DeltaTime

		// Update logic with our Vector3D class
		PhysicWorld::getInstance()->ApplyForces(dt);

		renderImGUIFrame(); //Create the ImGUI Frame


		// Update matrix
		glm::mat4 viewProjection = Projection * View;

		for (Particle* particle : PhysicWorld::getInstance()->getParticles())
		{
			Model = glm::translate(glm::vec3(particle->GetPosition().getX(), particle->GetPosition().getY(), particle->GetPosition().getZ()));
			mvp = viewProjection * Model;
			paintGL();
		}

		// Real draw for ImGui in foreground 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


	} // Check if escape is pressed to close the window
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

