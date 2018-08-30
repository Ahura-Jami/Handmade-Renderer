#include "engine.h"

#include <iostream>
#include <engine.h>


Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::Destroy()
{
	// terminate glfw to clear all previously allocated GLFW resources.
	glfwTerminate();
}

bool Engine::Init()
{
	bool successfully_created = true;

	// Instantiate the GLFW window
	glfwInit();

	// Configure the GLFW window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	// addresses a compilation issue on OS X
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
#endif

	window = glfwCreateWindow(window_width, window_height, "Engine", NULL, NULL);

	if (window == NULL)
	{
		puts("Failed to create GLFW window");
		glfwTerminate();
		successfully_created = false;
	}
	glfwMakeContextCurrent(window);

	// Window resize callback function
	glfwSetFramebufferSizeCallback(window, Engine::FrameBufferSizeCallback);

	// Load all OpenGL function pointers through GLUT
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		puts("Failed to initialize GLAD");
		successfully_created = false;
	}

	return successfully_created;
}

void Engine::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Engine::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Engine::Render()
{
	if (!Init())
	{
		return;
	}

	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// User inputs
		ProcessInput();

		// Rendering facilities
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffer and pull IO events (keys pressed/released, mouse moved, etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Destroy and delete all allocated opengl and glfw resources
	Destroy();
}


