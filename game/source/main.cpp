#include <iostream>
#include <memory>
#include <cstring>
#include <resource-manager.h>

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
	auto shader = ResourceManager::LoadShader(
			"triangle",
			PROJECT_DIR + std::string("/game/shaders/triangle_shader.vert"), // vertex shader
			PROJECT_DIR + std::string("/game/shaders/triangle_shader.frag") // fragment shader
	);

	// Load all the textures
	auto wood_texture = ResourceManager::LoadTexture(
			"wood",
			PROJECT_DIR + std::string("/game/textures/wooden-container.jpg")
	);

	auto wall_texture = ResourceManager::LoadTexture(
			"wall",
			PROJECT_DIR + std::string("/game/textures/wall.jpg")
	);

	auto smiley_texture = ResourceManager::LoadTexture(
			"smiley",
			PROJECT_DIR + std::string("/game/textures/awesomeface.png")
	);

	// Create rectangle
	// Define vertices and their appropriate data
	float triangle_vertices[] = {
			-1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // bottom left
			 0.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
			-0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,	0.5f, 1.0f  // top
	};
	auto triangle = Triangle(triangle_vertices);

	// Pass the shader and texture to the triangle
	triangle.SetShader(shader);
	triangle.AddTexture(wall_texture);
	triangle.AddTexture(smiley_texture);
	engine->Register(triangle);

	// Create rectangle
	float rectangle_vertices[] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 1.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			 0.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	auto rectangle = Rectangle(rectangle_vertices);
	rectangle.SetShader(shader);
	rectangle.AddTexture(wood_texture);
	rectangle.AddTexture(smiley_texture);
	engine->Register(rectangle);

	// Enable wireframe mode
//	engine->ToggleWireframe();

	// Render the registered actors
	engine->Render();
}
