#include "Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>

#include "ResourceManager.h"
#include "Camera.h"
#include "Types.h"

void MouseMovementCallback(GLFWwindow* window, double mouse_position_x, double mouse_position_y);

void MouseScrollCallback(GLFWwindow* window, double offset_x, double offset_y);

Camera Engine::scene_camera = Camera();

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
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		successfully_created = false;
	}
	glfwMakeContextCurrent(window);

	// Window resize callback function
	glfwSetFramebufferSizeCallback(window, Engine::FrameBufferSizeCallback);

	// Load all OpenGL function pointers through GLUT
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		successfully_created = false;
	}

	//TODO(Ahura): find a better place for these (See also TODO for scene_camera member in Engine header)
	// Tell GLFW to capture the mouse cursor (but do not hide it)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Register mouse movement callback
	glfwSetCursorPosCallback(window, MouseMovementCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);

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

	// TODO(Ahura): A better solution would be to allow each class (actor) register its inputs
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		scene_camera.MoveForward(InputKey::W, delta_time);
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		scene_camera.MoveForward(InputKey::S, delta_time);
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		scene_camera.MoveRight(InputKey::A, delta_time);
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		scene_camera.MoveRight(InputKey::D, delta_time);
	}

}

void Engine::Render()
{
	glEnable(GL_DEPTH_TEST);

	/** Time of last frame */
	float time_last_frame = 0.0f;

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
		// Rendering facilities
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// User inputs
		ProcessInput();

		// We put in the render loop because mouse scroll callback will update the field_of_view and
		// hence this matrix must be updated
		glm::mat4 projection_matrix = glm::perspective(
				glm::radians(scene_camera.GetCurrentFieldOfView()),
				static_cast<float>(window_width)/ static_cast<float>(window_height),
				scene_camera.GetNearPlane(),
				scene_camera.GetFarPlane()
		);

		// TODO(Ahura): Maybe register this with other actors (objects)?
		scene_camera.Tick(delta_time);

		for (Actor& actor : actors)
		{
			// Call actor's tick function
			actor.Tick(delta_time);

			// Activate the program and set it as current program to be used for subsequent drawing commands.
			actor.shader.Use();

			actor.shader.SetMatrix4("transform",
					projection_matrix * scene_camera.GetViewMatrix() * actor.GetModelMatrix());

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

		// Processes delta time
		const auto time_current_frame = static_cast<float>(glfwGetTime());
		delta_time = time_current_frame - time_last_frame;
		time_last_frame = time_current_frame;
	}

	// Destroy and delete all allocated opengl and glfw resources
	Destroy();
}

/**
 * Callback for mouse movements that is registered in GLFW
 */
// TODO(Ahura): Not ideal to have this callback here in the engine class itself.
void MouseMovementCallback(GLFWwindow* window, double mouse_position_x, double mouse_position_y)
{
	Engine::scene_camera.ProcessMouseMovement(glm::vec2(mouse_position_x, mouse_position_y));
}

/**
 * Callback for mouse scroll that is registered in GLFW
 */
// TODO(Ahura): Not ideal to have this callback here in the engine class itself.
void MouseScrollCallback(GLFWwindow* window, double offset_x, double offset_y)
{
	Engine::scene_camera.Zoom(offset_y);
}