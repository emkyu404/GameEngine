#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <string>
#include <map>

#include <iostream>
#include <vector>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "LoadShader.h"

// Inclut GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLM/gtx/transform.hpp>

//Utilities class
#include "Shader.h"
#include "Quaternion.h"

// Moteur
#include <Particle.hpp>

//Shapes
#include "Cube.h"
#include "Quad.h"

//Primitives
#include "Primitive.h"
#include "Plane.h"

//PhysicWorld
#include "PhysicWorld.h"

//Forces
#include "GravityForceGenerator.h"
#include "DragForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "ParticleSpringForceGenerator.h"
#include "RigidSpringForceGenerator.h"
#include "SimpleForceGenerator.h"

//Camera
#include "Camera.h"
#include <Matrix33.h>
#include <Matrix34.h>

#define MAX_NUMBER_PHYSICOBJECT 1000

using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static GLFWwindow* window; //GLFW window context

static GLuint MatrixID;
static Shape* grid;

static Shader* physicObjectShader;
static mat4 view,projection ,mvp, model;

static PhysicWorld physicWorld = PhysicWorld();
static int physicObjectCount = 5;
static Vector3D offsetPhysicObject = Vector3D(3, 0, 0);

// Forces
static ObjectForceGenerator* gravity = new GravityForceGenerator(); // Gravity force is common to every particle
static ObjectForceGenerator* drag = new DragForceGenerator(); 
//static ParticleForceGenerator* spring = new ParticleSpring();
//static ParticleForceGenerator* anchoredSpring = new ParticleAnchoredSpring();
static ObjectForceGenerator* buoyancy = new BuoyancyForceGenerator();

static map<PhysicObject*, Shape*> shapeRegistry;

int detectorNumberParticle = 0; 

//time logic
float dt = 0.0f; //deltaTime
float lastFrame = 0.0f;
bool firstMouse = true;

//mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

Camera camera = Camera(0.0f, 0.0f, 30.0f);
static float camSpeed = 2.5f;


void initGL();
void paintGL();
void initPhysicObject();
void setupImGUI(GLFWwindow* window, const char* glsl_version);
void renderImGUIMainFrame();
void initProjectionMatrix();
void mainLoop();
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

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
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);


	setupImGUI(window, glsl_version); // Setup ImGUI

	initGL(); // Initialize shapes to be rendered

	initProjectionMatrix(); // Initialize projection matrix

	initPhysicObject(); // Initialize PhysicObject

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
	physicObjectShader = new Shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
}

void paintGL() {
	//Clear screen
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.getViewMatrix();
	
	
	for (PhysicObject* physicObject : PhysicWorld::getInstance()->getPhysicObjects())
	{
		model = glm::translate(glm::vec3(physicObject->getPosition().getX(), physicObject->getPosition().getY(), physicObject->getPosition().getZ()));
		if (dynamic_cast<RigidBody*>(physicObject) != nullptr) {
			RigidBody* rigidbody = dynamic_cast<RigidBody*>(physicObject);
			glm::quat quat = glm::quat(rigidbody->getOrientation().getW(), rigidbody->getOrientation().getI(), rigidbody->getOrientation().getJ(), rigidbody->getOrientation().getK());
			glm::mat4 rot = glm::toMat4(quat);
			model = rot * model;
		}
		mvp = projection * view * model;
		// Précision du shader à utiliser
		physicObjectShader->activate();

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		GLint color_location = glGetUniformLocation(physicObjectShader->programID, "my_color");
		if (dynamic_cast<RigidBody*> (physicObject) != nullptr) {
			RigidBody* rigidbody = dynamic_cast<RigidBody*>(physicObject);
			if (rigidbody->getScale().getX() == 0 || rigidbody->getScale().getY() == 0 || rigidbody->getScale().getZ() == 0) {
				float color[3] = { 0.0f, 0.8f, 0.0f };
				glUniform3fv(color_location, 1, color);
			}
			else {
				float color[3] = { 1.0f, 0.8f, 0.2f };
				glUniform3fv(color_location, 1, color);
			}
		}
		else if(dynamic_cast<Particle*> (physicObject) != nullptr) {
			float color[3] = { 1.0f, 0.0f, 0.0f };
			glUniform3fv(color_location, 1, color);
		}
		auto search = shapeRegistry.find(physicObject);
		if ( search != shapeRegistry.end()) {
			search->second->draw();
		}
		else {
			Shape* objectShape;
			if (dynamic_cast<RigidBody*>(physicObject) != nullptr) {
				RigidBody* rigidbody = dynamic_cast<RigidBody*>(physicObject);
				Vector3D scale = rigidbody->getScale();
				objectShape = new Cube(rigidbody->getScale());
			}
			else {
				objectShape = new Cube(Vector3D(2,1,2));
			}
			objectShape->init();
			shapeRegistry.insert({ physicObject, objectShape });
			objectShape->draw();
		}
	}
}

void initPhysicObject() 
{
	
	//PhysicWorld::getInstance()->addRigidBody(Vector3D(-0.3f,0,0), Vector3D(2,1,2));
	//PhysicWorld::getInstance()->addRigidBody(Vector3D(7, 0, 0));
	//PhysicWorld::getInstance()->addRigidBody(Vector3D(-7, 0, 0));
	RigidBody* plane = new RigidBody(Vector3D(0, -10, 0), Vector3D(10, 0, 10));
	Plane* planePrimitive = new Plane(plane, Vector3D(0, 1, 0), -10);
	PhysicWorld::getInstance()->addRigidBody(Vector3D(0,0,0));
	PhysicWorld::getInstance()->addRigidBody(plane, planePrimitive); // plane


	vector<PhysicObject*> rigidbodies = PhysicWorld::getInstance()->getPhysicObjects();

	float rest_length = 3;
	float spring_constant = 1;

	//RigidSpringForceGenerator* rsfg1 = new RigidSpringForceGenerator(rigidbodies[1], spring_constant, rest_length, Vector3D(2, 0, 0), Vector3D(-1, 0, 0));
	//RigidSpringForceGenerator* rsfg2 = new RigidSpringForceGenerator(rigidbodies[2], spring_constant, rest_length, Vector3D(-2, 0, 0), Vector3D(1, 0, 0));


	
	//PhysicWorld::getInstance()->addForceEntry(rigidbodies[0], rsfg1);
	//PhysicWorld::getInstance()->addForceEntry(rigidbodies[0], rsfg2);
	//PhysicWorld::getInstance()->addForceEntry(rigidbodies[0], gravity);
	//PhysicWorld::getInstance()->addForceEntry(rigidbodies[0], drag);
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
	*out_text = "Particle"; 

	return true;
}

void renderImGUIParticlesList()
{
	ImGui::Begin("Particles");

	PhysicWorld* instance = PhysicWorld::getInstance();
	float particleIndex = 0.0f; 
	int numberParticles = instance->getNumberOfParticles(); 

	for (PhysicObject* physicObject : PhysicWorld::getInstance()->getParticles())
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
			Vector3D position = physicObject->getPosition();
			Vector3D velocity = physicObject->getVelocity();
			Vector3D acceleration = physicObject->getAcceleration();

			ImGui::Text("Position : (%.1f, %.1f, %.1f)", position.getX(), position.getY(), position.getZ()); 
			ImGui::Text("Velocity : (%.1f, %.1f, %.1f)", velocity.getX(), velocity.getY(), velocity.getZ());
			ImGui::Text("Acceleration : (%.1f, %.1f, %.1f)", acceleration.getX(), acceleration.getY(), acceleration.getZ());

			//if (ImGui::Button(text_mass.c_str()))
			//{
			//	printf("%f", particle->GetInverseMass());
			//}

			if (ImGui::Button(text_gravity.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, gravity);
			}

			if (ImGui::Button(text_drag.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, drag);
			}

			if (ImGui::Button(text_buoyancy.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, buoyancy);
			}


			static int selectedParticleSpring = 0;

			vector<Particle*> particlesVector = PhysicWorld::getInstance()->getParticles();
			particlesVector.erase(remove_if(particlesVector.begin(), particlesVector.end(), [&](const Particle* p) { return p == physicObject; }), particlesVector.end());;
			const char* out_text[MAX_NUMBER_PHYSICOBJECT];

			ImGui::Combo(text_particleList.c_str(), &selectedParticleSpring, *VectorOfStringGetter,
				(void *) &particlesVector, particlesVector.size());

			detectorNumberParticle = 0; 

			if (ImGui::Button(text_spring.c_str()))
			{
				ObjectForceGenerator* spring = new ParticleSpringForceGenerator(particlesVector[selectedParticleSpring]);
				PhysicWorld::getInstance()->addForceEntry(physicObject, spring);
			}

			
			if (ImGui::Button(text_remove.c_str()))
			{
				PhysicWorld::getInstance()->removePhysicObject(physicObject);
			}
		}
	}

	ImGui::End();
}

void renderImGUIRigidBodiesList()
{
	ImGui::Begin("Rigidbodies");

	PhysicWorld* instance = PhysicWorld::getInstance();
	float rigidIndex = 0.0f;
	int numberRigidbodies = instance->getNumberOfRigidBodies();

	for (RigidBody* physicObject : PhysicWorld::getInstance()->getRigidBodies())
	{
		rigidIndex++;
		ImGui::Text("Rigidbody %.0f", rigidIndex);

		// Declare string names with ID to make sure GUI is ok with the buttons
		string text_customization_rigidbody = std::string("Customization rigid body##") + std::to_string(rigidIndex);
		string text_mass = std::string("Set inverse mass##") + std::to_string(rigidIndex);
		string text_gravity = std::string("Apply Gravity##") + std::to_string(rigidIndex);
		string text_drag = std::string("Apply Drag##") + std::to_string(rigidIndex);
		string text_buoyancy = std::string("Apply Buoyancy##") + std::to_string(rigidIndex);
		string text_spring = std::string("Apply Spring##") + std::to_string(rigidIndex);
		string text_remove = std::string("Remove RigidBody##") + std::to_string(rigidIndex);
		string text_rigidbodyList = std::string("Rigidbody List##") + std::to_string(rigidIndex);
		string text_slider_position = std::string("Slider Position##") + std::to_string(rigidIndex);
		string text_slider_orientation = std::string("Slider Orientation##") + std::to_string(rigidIndex);

		if (ImGui::CollapsingHeader(text_customization_rigidbody.c_str()))
		{
			Vector3D position = physicObject->getPosition();
			Vector3D velocity = physicObject->getVelocity();
			Vector3D acceleration = physicObject->getAcceleration();
			Quaternion orientation = physicObject->getOrientation();

			Vector3D torque = physicObject->getTorque();
			Vector3D angularAcc = physicObject->getAngularAcceleration();

			float x_pos = position.getX();
			float y_pos = position.getY();
			float z_pos = position.getZ();
			float posArr[3] = { x_pos,y_pos,z_pos };

			
			if (ImGui::SliderFloat3(text_slider_position.c_str(), posArr, -10.0f, 10.0f, "%.01f")) {
				physicObject->setPosition(Vector3D(posArr[0], posArr[1],posArr[2]));
			}

			/*
			if (ImGui::SliderFloat3(text_slider_orientation.c_str(), oriArr, -180.0f, 180.0f, "%.1f")) {
				physicObject->setOrientation(Vector3D(posArr[0], posArr[1], posArr[2]));
			}*/

			ImGui::Text("Position : (%.1f, %.1f, %.1f)", position.getX(), position.getY(), position.getZ());
			ImGui::Text("Velocity : (%.1f, %.1f, %.1f)", velocity.getX(), velocity.getY(), velocity.getZ());
			ImGui::Text("Acceleration : (%.1f, %.1f, %.1f)", acceleration.getX(), acceleration.getY(), acceleration.getZ());


			ImGui::Text("Orientation : (%.1f, %.1f, %.1f, %.1f)", orientation.getW(), orientation.getI(), orientation.getJ(), orientation.getK());
			ImGui::Text("Torque : (%.1f, %.1f, %.1f)", torque.getX(), torque.getY(), torque.getZ());
			ImGui::Text("Angular Acceleration : (%.1f, %.1f, %.1f)", angularAcc.getX(), angularAcc.getY(), angularAcc.getZ());

			//if (ImGui::Button(text_mass.c_str()))
			//{
			//	printf("%f", particle->GetInverseMass());
			//}

			if (ImGui::Button(text_gravity.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, gravity);
			}

			if (ImGui::Button(text_drag.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, drag);
			}

			if (ImGui::Button(text_buoyancy.c_str()))
			{
				PhysicWorld::getInstance()->addForceEntry(physicObject, buoyancy);
			}


			static int selectedParticleSpring = 0;

			vector<RigidBody*> rigidbodiesVector = PhysicWorld::getInstance()->getRigidBodies();
			rigidbodiesVector.erase(remove_if(rigidbodiesVector.begin(), rigidbodiesVector.end(), [&](const RigidBody* p) { return p == physicObject; }), rigidbodiesVector.end());;
			const char* out_text[MAX_NUMBER_PHYSICOBJECT];

			ImGui::Combo(text_rigidbodyList.c_str(), &selectedParticleSpring, *VectorOfStringGetter,
				(void*)&rigidbodiesVector, rigidbodiesVector.size());

			detectorNumberParticle = 0;

			if (ImGui::Button(text_spring.c_str()))
			{
				ObjectForceGenerator* spring = new RigidSpringForceGenerator(rigidbodiesVector[selectedParticleSpring], Vector3D(0, 0, 0), Vector3D(0, 0, 0));
				PhysicWorld::getInstance()->addForceEntry(physicObject, spring);
			}

			
			if (ImGui::Button(text_remove.c_str()))
			{
				PhysicWorld::getInstance()->removePhysicObject(physicObject);
			}
		}
	}

	ImGui::End();
}
void renderImGUIContactsInfo() {
	PhysicWorld* instance = PhysicWorld::getInstance();
	int contactIndex = 0;
	ImGui::Begin("Contacts");
	for (auto contact : instance->getContacts()) {
		contactIndex++;
		Vector3D pointOfContact, normal;
		float restitution, penetration;
		pointOfContact = contact.getPoint();
		normal = contact.getNormal();
		restitution = contact.getRestitution();
		penetration = contact.getPenetration();

		string text_contact_info = std::string("Contact ##") + std::to_string(contactIndex);

		if (ImGui::CollapsingHeader(text_contact_info.c_str()))
		{
			ImGui::Text("Point of contact : (%.1f, %.1f, %.1f)", pointOfContact.getX(), pointOfContact.getY(), pointOfContact.getZ());
			ImGui::Text("Normal : (%.4f, %.4f, %.4f)", normal.getX(), normal.getY(), normal.getZ());
			ImGui::Text("Interpenetration : %.1f", penetration);
			ImGui::Text("restitution : %.1f",restitution);
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
		instance->addParticle(offsetPhysicObject * instance->getNumberOfPhysicObject());
	}

	if (ImGui::Button("Add Rigidbody"))
	{
		instance->addRigidBody(offsetPhysicObject * instance->getNumberOfPhysicObject());
	}

	if (ImGui::Button("Apply Gravity"))
	{
		for (PhysicObject* particle : instance->getPhysicObjects())
		{
			instance->addForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Disable Gravity"))
	{
		for (PhysicObject* particle : instance->getPhysicObjects())
		{
			instance->removeForceEntry(particle, gravity);
		}
	}

	if (ImGui::Button("Apply Drag"))
	{
		for (PhysicObject* physicObject : instance->getPhysicObjects())
		{
			instance->addForceEntry(physicObject, drag);
		}
	}

	if (ImGui::Button("Disable Drag"))
	{
		for (PhysicObject* physicObject : instance->getPhysicObjects())
		{
			instance->removeForceEntry(physicObject, drag);
		}
	}

	if (ImGui::Button("Apply Buoyancy"))
	{
		for (PhysicObject* physicObject : instance->getPhysicObjects())
		{
			instance->addForceEntry(physicObject, buoyancy);
		}
	}

	if (ImGui::Button("Disable Buoyancy"))
	{
		for (PhysicObject* physicObject : instance->getPhysicObjects())
		{
			instance->removeForceEntry(physicObject, buoyancy);
		}
	}

	/*
	if (ImGui::Button("Remove all particles"))
	{
		for (PhysicObject* particle : instance->getPhysicObjects())
		{
			instance->removeParticle(particle);
		}
	}*/

	if (ImGui::Button("Reset"))
	{
		for (PhysicObject* physicObject : instance->getPhysicObjects())
		{
			if (dynamic_cast<RigidBody*>(physicObject) != nullptr) {
				RigidBody* rigidbody = dynamic_cast<RigidBody*>(physicObject);
				rigidbody->reset();
			}
			else {
				physicObject->reset();
			}
		}
		instance->Resume();
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
	renderImGUIRigidBodiesList(); 
	rendererImGUICamera(); 

	if (PhysicWorld::getInstance()->getContacts().size() > 0) {
		renderImGUIContactsInfo();
	}
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
	MatrixID = glGetUniformLocation(physicObjectShader->programID, "MVP");
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

/*
void testMatrix() {
	float valuesM1[12] = { 1.0f, 2.0f, 0.0f, 1.0f, 4.0f, 3.0f, -1.0f, 2.0f, 2.0f, 7.0f, 9.0f, 0.0f };
	float valuesM2[12] = { 7.0f, 6.0f, 2.0f, 0.0f, -1.0f, 5.0f, 3.0f, 1.0f, 4.0f, 8.0f, 0.0f, -4.0f };
	Matrix34 m1 = Matrix34(valuesM1);
	Matrix34 m2 = Matrix34(valuesM2);

	m1.printMatrix34();
	m1.getInverse().printMatrix34();

	Quaternion quatTest = Quaternion();
	quatTest.print();
	quatTest.normalized();
	quatTest.print();

	Quaternion quatTestNotEmpty = Quaternion(3, 2, 1, 1);
	quatTestNotEmpty.print();
	quatTestNotEmpty.normalized();
	quatTestNotEmpty.print();

	quatTest.print();
	quatTest = quatTestNotEmpty * quatTestNotEmpty;
	quatTest.print();
}*/
