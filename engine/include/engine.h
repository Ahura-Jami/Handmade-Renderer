#ifndef ENGINE_LIBRARY_H_
#define ENGINE_LIBRARY_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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

private:
	/**
	 * Initializes a GLFW window object
	 * @return true if window is successfully created, false otherwise.
	 */
	bool Init();

	void Destroy();

	void Render();

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

};

#endif