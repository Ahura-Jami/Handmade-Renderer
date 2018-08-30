#include <iostream>
#include <memory>

#include "engine.h"

int main()
{
	auto engine = std::make_unique<Engine>();

	engine->Render();
}

//void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
//void ProcessInput(GLFWwindow* window);
//
//// Settings
//const unsigned int kScreenWidth = 800;
//const unsigned int kScreenHeight = 600;
//
//int main()
//{
//	glfwInit();
//
//	// Configure the GLFW window
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	// addresses a compilation issue on OS X
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
//#endif
//
//	// Create a window object
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		puts("Failed to create GLFW window");
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Window resize callback function
//	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
//
//	// Load all OpenGL function pointers through GLUT
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		puts("Failed to initialize GLAD");
//		return -1;
//	}
//
//	// Render loop
//	while(!glfwWindowShouldClose(window))
//	{
//		// User inputs
//		ProcessInput(window);
//
//		// Rendering facilities
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Swap buffer and pull IO events (keys pressed/released, mouse moved, etc.)
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// terminate glfw to clear all previously allocated GLFW resources.
//	glfwTerminate();
//
//	return 0;
//}
//
///**
// * A Callback function for windows resize event that gets executed whenever the size of the widnow
// * changes (either by user or OS itself)
// * @param [in] window A window object created by a call to glfwCreateWindow
// * @param [in] width The width of the window in pixels
// * @param [in] height The height of the window in pixels
// */
//void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
///**
// * Processes all the inputs: queries GLFW whether relevant keys are pressed/released this frame
// * and reacts accordingly
// * @param [in] window A window object created by a call to glfwCreateWindow
// */
//void ProcessInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}