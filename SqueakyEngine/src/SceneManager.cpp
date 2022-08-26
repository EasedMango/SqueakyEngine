#include "SceneManager.h"
#include "Events.h"
#include <iostream>
#include "Scene1.h"
#include "Scene.h"
#include "Window.h"
#include <glm/glm.hpp>
#include "Logger.h"
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void SceneManager::Run()
{

	glfwSetWindowUserPointer(window->GetWindow(), this);
	currentScene = new Scene1();
	currentScene->OnCreate();
	glfwSetFramebufferSizeCallback(window->GetWindow(), framebuffer_size_callback);
	Logger::Info( "Starting main loop" );
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window->GetWindow());

		/* Poll for and process events */
		glfwPollEvents();

		//GLFWkeyfun lol;
		glfwSetKeyCallback(window->GetWindow(), key_callback);

		currentScene->Update(0.01333333f);
		currentScene->Render();


	}
	




	glfwDestroyWindow(window->GetWindow());
	glfwTerminate();
}

void SceneManager::HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	currentScene->key_callback(window, key, scancode, action, mods);
}


bool SceneManager::Initialize(const char* name_, int width_, int height_)
{
	if (!glfwInit())
	{
		glfwSetErrorCallback(errorGLFW);
		// Initialization failed
	}
	


	window = new Window(1280, 720, "Main");
	events = new Events(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	
	return false;
}


