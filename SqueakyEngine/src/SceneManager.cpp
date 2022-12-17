
#include "SceneManager.h"
#include "Events.h"
#include <iostream>
#include "Scene.h"
#include "Window.h"
#include <glm/glm.hpp>
#include "Components/Logger.h"
#include "Components/Camera.h"
#include "Components/Shader.h"
#include "Geometry/BasicShapes.h"
#include "Components/Gui.h"
#include "Input.h"
#include <Renderer.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 

static void errorGLFW(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<SceneManager*>(glfwGetWindowUserPointer(window))->HandleEvents(window, key, scancode, action, mods);
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {

		int check = glfwGetInputMode(window, GLFW_CURSOR);

		switch (check) {
		case GLFW_CURSOR_DISABLED:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case GLFW_CURSOR_NORMAL:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			break;

		default:

			break;

		}
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Input::GetInstance().handle_clicks(window, button, action, mods);
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 pos(xpos, ypos);
	Input::GetInstance().SetMousePos(pos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().SetScroll(xoffset, yoffset);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Run(int scene)
{



	curTime = 0;
	glfwSetWindowUserPointer(window->GetWindow(), this);
	currentScene = scenes[scene];
	currentScene->OnCreate();
	gui = new Gui(window->GetWindow());

	glfwSetFramebufferSizeCallback(window->GetWindow(), SetBuffer);
	glfwSetInputMode(window->GetWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetCursorPosCallback(window->GetWindow(), cursor_position_callback);
	glfwSetMouseButtonCallback(window->GetWindow(), mouse_button_callback);
	glfwSetScrollCallback(window->GetWindow(), scroll_callback);
	gui->OnCreate();

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//Renderer render;
	Logger::Info("Starting main loop");
	while (!glfwWindowShouldClose(window->GetWindow()))
	{

		prevTime = curTime;
		curTime = glfwGetTime();
		deltaTime = curTime - prevTime;
		
		int width, height;
		glfwGetFramebufferSize(window->GetWindow(), &width, &height);
		Input::GetInstance().SetViewportSize(width, height);
		Input::GetInstance().handle_input(deltaTime);
		currentScene->Update(deltaTime);
		currentScene->Render();
		Renderer::GetInstance().Render();
		static int count = 0;


		// Rendering
		RenderGui();

		/* Swap front and back buffers */
		glfwSwapBuffers(window->GetWindow());
		//glfwSwapInterval(1);
		/* Poll for and process events */
		glfwPollEvents();
		//	printf("fs");
			//GLFWkeyfun lol;
		glfwSetKeyCallback(window->GetWindow(), key_callback);
		if (Input::GetInstance().GetScrollWheel() != 0) {
			Input::GetInstance().SetScroll(0, 0);
		}
	}





	glfwDestroyWindow(window->GetWindow());
	glfwTerminate();
}

void SceneManager::LoadScene(Scene* scene)
{
	currentScene->OnDestroy();
	currentScene = scene;
	currentScene->OnCreate();

}


void SceneManager::HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	Input::GetInstance().handle_key(window, key, scancode, action, mods);
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		LoadScene(scenes.back());
	}
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
	printf("buffer");


	glViewport(0, 0, width, height);
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


	Input::GetInstance().RenderGui();
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
