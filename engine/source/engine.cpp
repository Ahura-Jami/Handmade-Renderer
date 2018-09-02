#include "engine.h"

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resource_manager.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::Destroy()
{
	// Clear all textures and shaders
	ResourceManager::Clear();

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
	glEnable(GL_DEPTH_TEST);

//	glm::mat4 trans = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
//
	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f),
									  static_cast<float>(window_width)/ static_cast<float>(window_height),
									  0.1f,
									  100.0f
	);

	// Tell OpenGL to which texture unit each shader sampler belongs to by setting
	// each sampler using glUniform1i. We only have to set this once, so we can do
	// this before we enter the render loop
	for (auto& actor : actors)
	{
		actor.shader.Use();

		// The id of texture which allows for the texture to be mapped
		// to its specific uniform in the fragment shader.
		for (int id = 0; id < actor.textures.size(); ++id)
		{
			actor.shader.SetInteger(("texture" + std::to_string(id)).c_str(), id);
		}
	}

	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// User inputs
		ProcessInput();

		// Rendering facilities
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& actor : actors)
		{
			// Activate the program and set it as current program to be used for subsequent drawing commands.
			actor.shader.Use();

			// Processes the transformations
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

			actor.SetWorldRotation(glfwGetTime() * 20.0f, glfwGetTime() * 10.0f, 0.0f);
			actor.shader.SetMatrix4("transform", projection_matrix * view * actor.GetModelMatrix());

			// Loop over the textures and bind them each
			for (int id = 0; id < actor.textures.size(); ++id)
			{
				// Activate the texture unit first before binding texture
				glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + id));
				actor.textures[id].Bind();
			}
			// Bind vertex array object
			glBindVertexArray(actor.vertex_array_object);

			// Call the actor's draw command
			actor.draw_function();

			// Unbind the textures
			glBindTexture(GL_TEXTURE_2D, 0);

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


