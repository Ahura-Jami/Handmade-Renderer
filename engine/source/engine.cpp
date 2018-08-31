#include "engine.h"

#include <iostream>
#include <cmath>

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::Destroy()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	for(auto& actor : actors)
	{
		glDeleteVertexArrays(1, &actor.vertex_array_object);
		glDeleteBuffers(1, &actor.vertex_buffer_object);
		glDeleteBuffers(1, &actor.element_buffer_object);
	}

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
	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// User inputs
		ProcessInput();

		// Rendering facilities
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (const auto& actor : actors)
		{
			// Activate the program and set it as current program to be used for subsequent drawing commands.
			glUseProgram(actor.shader.GetShaderProgram());

			// Bind vertex array object
			glBindVertexArray(actor.vertex_array_object);

			// Call the draw command
			actor.draw_function();

			// Unbind the vertex array object
			glBindVertexArray(0);
		}

		// Swap buffer and pull IO events (keys pressed/released, mouse moved, etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Destroy and delete all allocated opengl and glfw resources
	Destroy();
}


