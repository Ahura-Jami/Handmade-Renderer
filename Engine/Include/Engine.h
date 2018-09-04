#ifndef ENGINE_LIBRARY_H_
#define ENGINE_LIBRARY_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Actor.h"
#include "Camera.h"

class Engine
{
public:
	/**
	 * Default constructor
	 */
	Engine();

	/**
	 * Default destructor
	 */
	~Engine();

	/**
	 * Initializes a GLFW window object
	 * @return true if window is successfully created, false otherwise.
	 */
	bool Init();

	/**
	 * Initializes the render loop and processes all rendering commands.
	 */
	void Render();

	/**
	 * Register a renderable object that inherits from Actor
	 * @param [in] actor An object that inherits from Actor
	 */
	void Register(std::shared_ptr<Actor> actor)
	{
		actors.emplace_back(actor);
	}

	/**
	 * Toggles the wireframe mode (initial wireframe mode is off)
	 */
	void ToggleWireframe()
	{
		// From OpenGL Doc: params returns two values: symbolic constants indicating whether front-facing and
		// back-facing polygons are rasterized as points, lines, or filled polygons.
		GLint polygon_mode[2];
		glGetIntegerv(GL_POLYGON_MODE, polygon_mode);

		switch(polygon_mode[0])
		{
			case GL_LINE:
			{
				// Wiremode is one, turn it off by switching back to fill mode.
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			}

			case GL_FILL:
			{
				// Wiremode is off, turn it on by switching to line mode.
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			}
		}
	}

private:
	/**
	 * Deallocates all OpenGL's and GLFW's resources.
	 * Called when window is closed and render loop exists.
	 */
	void Destroy();

	/**
	 * A Callback function for windows resize event that gets executed whenever the size of the widnow
	 * changes (either by user or OS itself)
	 * @param [in] window A window object created by a call to glfwCreateWindow
	 * @param [in] width The width of the window in pixels
	 * @param [in] height The height of the window in pixels
	 */
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

	/**
	 * Processes all the inputs: queries GLFW whether relevant keys are pressed/released this frame
	 * and reacts accordingly
	 * @param [in] window A window object created by a call to glfwCreateWindow
	 */
	void ProcessInput();


public:
	// TODO(Ahura): I don't like this being static, but I have to because it is used in
	// MouseMovementCallback and MouseScrollCallback. See if there is an alternative way
	// to capture mouse movements.
	static Camera scene_camera;

private:
	/**
	 * A GLFW Window Object that will be initialized in Init()
	 */
	GLFWwindow *window;

	/**
	 * Initial width of the window
	 */
	const unsigned int window_width = 800;

	/**
	 * Initial height of the window
	 */
	const unsigned int window_height = 600;

	/** Time it takes to render each frame */
	float delta_time = 0.0f;

	/**
	 * List of registered renderable objects
	 */
	 std::vector<std::shared_ptr<Actor>> actors;

};

#endif