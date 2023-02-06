
#include "SceneManager.h"
#include "Events.h"
#include <iostream>
#include "Scene.h"
#include "Window.h"
#include <glm/glm.hpp>
#include "Components/Logger.h"
#include "Components/Camera.h"
#define GLFW_INCLUDE_NONE
#include "Geometry/BasicShapes.h"
#include "Components/Gui.h"
#include "Input.h"
#include <Renderer.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 

static void errorGLFW(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
	const std::string errors = std::to_string(error) + " " + description;
	Logger::Info("GLFW initialization failed: " + errors);
}
void SceneManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<SceneManager*>(glfwGetWindowUserPointer(window))->HandleEvents(window, key, scancode, action, mods);
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {

		switch (int check = glfwGetInputMode(window, GLFW_CURSOR)) {
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
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Input::GetInstance().HandleClicks(window, button, action, mods);
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

}

static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 pos(xpos, ypos);
	Input::GetInstance().SetMousePos(pos);
}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().SetScroll(xoffset, yoffset);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	static_cast<SceneManager*>(glfwGetWindowUserPointer(window))->GetWindow()->SetWidthHeight(width, height);
	Input::GetInstance().SetViewportSize(width, height);
	std::cout << width << " " << height << std::endl;
}

SceneManager::SceneManager(): currentScene(nullptr), window(nullptr), actorManager(nullptr), gui(nullptr), curTime(0),
                              deltaTime(0),
                              prevTime(0), pause(false)
{
	Logger::InitLogger("EngineLog.txt");
	Logger::Info("Constructing SceneManager");
}

SceneManager::~SceneManager()
= default;

void SceneManager::Run(const int scene)
{
	Logger::Info("Starting Run");


	curTime = 0;
	glfwSetWindowUserPointer(window->GetWindow(), this);
	currentScene = scenes[scene];

	currentScene->OnCreate();
	gui = new Gui(window->GetWindow());

	glfwSetFramebufferSizeCallback(window->GetWindow(), SetBuffer);
	glfwSetWindowSizeCallback(window->GetWindow(), WindowSizeCallback);
	glfwSetInputMode(window->GetWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetCursorPosCallback(window->GetWindow(), CursorPositionCallback);
	glfwSetMouseButtonCallback(window->GetWindow(), MouseButtonCallback);
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);
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
		
		//Logger::Info("Handle Input");
		Input::GetInstance().HandleInput(deltaTime);
		//Logger::Info("Update");
		currentScene->Update(deltaTime);
		//Logger::Info("SceneRender");
		currentScene->Render();
		//Logger::Info("Renderer");
		Renderer::GetInstance().Render();
		static int count = 0;


		// Rendering
		RenderGui();

		/* Swap front and back buffers */
		glfwSwapBuffers(window->GetWindow());
		//glfwSwapInterval(1);
		/* Poll for and process events */
		glfwPollEvents();
		glfwSetKeyCallback(window->GetWindow(), KeyCallback);
		if (Input::GetInstance().GetScrollWheel() != 0) {
			Input::GetInstance().SetScroll(0, 0);
		}
	}




	Logger::Info("Ending Run");

	currentScene->OnDestroy();

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

	Input::GetInstance().HandleKey(window, key, scancode, action, mods);
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
		Logger::Info("GLFW initialization failed");
	}



	window = new Window(width_, height_, "Main");


	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Logger::FatalError("Failed to initialize OpenGL context");
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
