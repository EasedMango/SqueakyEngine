
#include "SceneManager.h"
#include "Events.h"
#include <iostream>
#include "Scene1.h"
#include "Scene.h"
#include "Window.h"
#include <glm/glm.hpp>
#include "Logger.h"
#include "Camera.h"
#include "Shader.h"
#include "Geometry/BasicShapes.h"
#include "Gui.h"
#include "Input.h"

#include <backends/imgui_impl_opengl3_loader.h>
static void errorGLFW(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<SceneManager*>(glfwGetWindowUserPointer(window))->HandleEvents(window, key, scancode, action, mods);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	
}



SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Run()
{  



	curTime = 0;
	glfwSetWindowUserPointer(window->GetWindow(), this);
	currentScene = new Scene1();
	currentScene->OnCreate();
	glfwSetFramebufferSizeCallback(window->GetWindow(), SetBuffer);
	gui = new Gui(window);
	gui->OnCreate();
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glfwSetInputMode(window->GetWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
	input = new Input();
	Logger::Info( "Starting main loop" );
	while (!glfwWindowShouldClose(window->GetWindow()))
	{

		prevTime = curTime;
		curTime = glfwGetTime();
		deltaTime = curTime - prevTime;
		currentScene->Update(deltaTime);
		currentScene->Render();


		// Rendering
		RenderGui();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window->GetWindow());
		//glfwSwapInterval(1);
		/* Poll for and process events */
		glfwPollEvents();

		//GLFWkeyfun lol;
		glfwSetKeyCallback(window->GetWindow(), key_callback);
	}
	




	glfwDestroyWindow(window->GetWindow());
	glfwTerminate();
}

void SceneManager::RenderGui()
{
	ImGui::SetNextWindowBgAlpha(0.0f);
	static bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();


	bool resetContext = false;

	int width = 1920 / 2;
	int height = 1080 / 2;



	ImGui::NewFrame();
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	if (gui->ReturnGuiIO()->MouseDown[0]) {
		pause != pause;
	}


	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.


	static float f = 0.0f;
	static int counter = 0;



	ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Scene Select");               // Display some text (you can use a format strings too)

	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state



	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	static float lastTick = 0;
	ImGui::Text("fps = %.3f", (deltaTime));
	lastTick = curTime;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	currentScene->RenderGui();
	gui->Render();
	if (resetContext) {
		if (gui->ReturnGuiIO() != nullptr) {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			gui->OnCreate();
		}
	}



}

void SceneManager::HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input->handle_key(window, key, scancode, action, mods);
	currentScene->key_callback(window, key, scancode, action, mods);
}


bool SceneManager::Initialize(const char* name_, int width_, int height_)
{
	pause = false;
	if (!glfwInit())
	{
		glfwSetErrorCallback(errorGLFW);
		// Initialization failed
	}



	window = new Window(width_, height_, "Main");


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}
	//glfwSwapInterval(1);
	//glfwGetFramebufferSize(window->GetWindow(), &width_, &height_);
	//glViewport(0, 0, width_, height_);
	//glfwSetFramebufferSizeCallback(window->GetWindow(), SetBuffer);

	//
	//std::cout << glGetString(GL_VERSION) << std::endl;


	return false;
}

 void SceneManager::SetBuffer(GLFWwindow* window, int width, int height) {
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}


