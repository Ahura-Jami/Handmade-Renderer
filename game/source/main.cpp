#include <iostream>
#include <memory>
#include <cstring>

#include "engine.h"

#include "shader.h"
#include "texture.h"

#include "triangle.h"
#include "rectangle.h"

int main()
{
	// Create the Engine object
	auto engine = std::make_unique<Engine>();

	// Initialize the engine
	if (not engine->Init())
		return -1;

	// Load the shaders
	auto shader = std::make_shared<Shader>(
			std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.vert", // vertex shader
			std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.frag"); // fragment shader

	// Load the texture
	auto wood_texture = std::make_shared<Texture>(
			std::string(PROJECT_DIR) + "/game/textures/wooden-container.jpg");

	// Create rectangle
	// Define vertices and their appropriate data
	float triangle_vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.5f, 1.0f  // top
	};
	auto triangle = Triangle(triangle_vertices);

	// Pass the shader and texture to the triangle
	triangle.SetShader(shader);
	triangle.SetTexture(wood_texture);
//	engine->Register(triangle);

	// Create rectangle
	float rectangle_vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	auto rectangle = Rectangle(rectangle_vertices);
	rectangle.SetShader(shader);
	rectangle.SetTexture(wood_texture);
	engine->Register(rectangle);

	// Enable wireframe mode
//	engine->ToggleWireframe();

	// Render the registered actors
	engine->Render();
}
