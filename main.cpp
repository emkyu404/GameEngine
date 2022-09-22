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

using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
GLFWwindow* window;
std::vector<Particle> particles;
float gravity = 0.0f;
Vector3D otherForce = Vector3D(0.0f, 0.0f, 0.0);
bool gravityEnabled = false;
bool otherForceEnabled = false;
int particleCount = 10;

void spawnParticles() {
	for (int i = 0; i < particleCount; ++i)
	{
		particles.push_back(Particle(Vector3D((-particleCount + i + 3.0f) * 2.5f, 0.0f, 0.0f)));
		particles[i].SetMass(i*10); 
	}
}

void setupImGUI(GLFWwindow* window, const char* glsl_version) {
	/* ImGUI setup */

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
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Ouvre une fenêtre et crée son contexte OpenGl
	
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialise GLEW
	glewExperimental = true; // Nécessaire dans le profil de base
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Enbale GL functions
	glEnable(GL_DEPTH_TEST);

	/* --- Création du triangle --- */
	/* Création du Vertex Array Object */
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/* Tableau de vertices qui représentent les sommets de notre triangle */
	static GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	

	/* -- Gestion du buffer (on fournit à OpenGL les informations du triangle) */
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);


	// Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	setupImGUI(window, glsl_version);
	


	// Chargement des shaders
	GLuint programID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");

	/* -- Matrice de projection -- */
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");


	
	// Initialisation
	spawnParticles();

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
		float dt = ImGui::GetIO().DeltaTime;

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
			spawnParticles();
		}
		ImGui::End();

		ImGui::Render();

		// Rendering
		glUseProgram(programID); // precise which shader to use, define earlier in the code

		// Update des matrices
		glm::mat4 viewProjection = Projection * View;

		for (auto&& particle : particles)
		{
			Model = glm::translate(glm::vec3(particle.GetPosition().getX(), particle.GetPosition().getY(), particle.GetPosition().getZ()));
			mvp = viewProjection * Model;

			// Send our transformation to the currently bound shader, in the "MVP" uniform
			// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		}

		// Real draw for ImGui in foreground 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


	} // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}