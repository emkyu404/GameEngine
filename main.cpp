#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

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

using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static GLFWwindow* window; //GLFW window context


std::vector<Particle> particles; // list of particles 

static float gravity = 0.0f;
static Vector3D otherForce = Vector3D(0.0f, 0.0f, 0.0);
static bool gravityEnabled = false;
static bool otherForceEnabled = false;
static int particleCount = 5;

static GLuint m_triangleProgramID, MatrixID;
static Triangle triangle;

static mat4 View,Projection ,mvp, Model;

void initializeGL() {
	// Chargement des shaders
	m_triangleProgramID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(m_triangleProgramID, "vertexPosition_modelspace");

	//Chargement OpenGL
	triangle.init(vertexPosition_modelspaceID);
}

void paintGL() {
	// Pr�cision du shader � utiliser
	glUseProgram(m_triangleProgramID);

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	triangle.draw();
}

void spawnParticles(int numberOfParticle) {
	for (int i = 0; i < numberOfParticle; i++)
	{
		particles.push_back(Particle(Vector3D((-numberOfParticle + i + 3.0f) * 2.5f, 0.0f, 0.0f)));
		particles[i].SetMass(i*10); 
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

void renderImGUIFrame() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Engine");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Checkbox("Gravity enbale", &gravityEnabled);
	ImGui::DragFloat("Gravity", &gravity, 0.1f, -10.f, 10.f);

	ImGui::Checkbox("Other force enbale", &otherForceEnabled);
	ImGui::DragFloat3("Other force", (float*)(&otherForce), 0.1f, -10.f, 10.f);

	if (ImGui::Button("Reset particle"))
	{
		particles.clear();
		spawnParticles(particleCount);
	}

	if (ImGui::Button("Add Particle") && particleCount < 10)
	{
		particleCount++;
		particles.clear();
		spawnParticles(particleCount);
	}

	if (ImGui::Button("RemoveParticle") && particleCount > 1) 
	{
		particleCount--;
		particles.clear();
		spawnParticles(particleCount);
	}

	ImGui::End();

	ImGui::Render();
}

void initProjectionMatrix() {
	/* -- Matrice de projection -- */
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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

		// Poll and handle events (inputs, window resize, etc.)
				// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
				// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
				// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
				// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Clear and setup viewport
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Time
		float dt = ImGui::GetIO().DeltaTime; //dt => DeltaTime

		// Update logic
		for (auto&& particle : particles)
		{
			Vector3D sumForces = Vector3D(0.0f, 0.0f, 0.0f);

			if (gravityEnabled)
				sumForces = sumForces + Vector3D(0.0f, gravity * particle.GetMass(), 0.0f);

			if (otherForceEnabled)
				sumForces = sumForces + otherForce;

			particle.Integrate(dt, sumForces);
		}

		renderImGUIFrame(); //Create the ImGUI Frame


		// Update des matrices
		glm::mat4 viewProjection = Projection * View;

		for (auto&& particle : particles)
		{
			Model = glm::translate(glm::vec3(particle.GetPosition().getX(), particle.GetPosition().getY(), particle.GetPosition().getZ()));
			mvp = viewProjection * Model;
			paintGL();
		}

		// Real draw for ImGui in foreground 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


	} // V�rifie si on a appuy� sur la touche �chap (ESC) ou si la fen�tre a �t� ferm�e
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

int main() 
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Decide GL+GLSL versions (for ImGUI)
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Ouvre une fen�tre et cr�e son contexte OpenGl
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialise GLEW
	glewExperimental = true; // N�cessaire dans le profil de base
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Enable GL functions
	glEnable(GL_DEPTH_TEST);

	// Assure que l'on peut capturer la touche d'�chappement enfonc�e ci-dessous
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	setupImGUI(window, glsl_version);
	
	initializeGL();

	initProjectionMatrix();

	// Initialisation
	spawnParticles(particleCount);

	mainLoop(); // Boucle de rendu
	

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}