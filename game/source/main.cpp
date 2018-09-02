#include <iostream>
#include <memory>
#include <cstring>

#include "engine.h"
#include "shader.h"
#include "texture.h"
#include "resource_manager.h"

#include "triangle.h"
#include "rectangle.h"
#include "cube.h"

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
//	engine->Register(triangle);

	// Create rectangle
	float rectangle_vertices[] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f,  0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 1.0f,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			 0.0f,  0.0f,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			 0.0f,  1.0f,  0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	auto rectangle = Rectangle(rectangle_vertices);
	rectangle.SetShader(shader);
	rectangle.AddTexture(wood_texture);
	rectangle.AddTexture(smiley_texture);
//	engine->Register(rectangle);

	// Load the cube shaders
	auto cube_shader = ResourceManager::LoadShader(
			"cube",
			PROJECT_DIR + std::string("/game/shaders/cube.vert"), // vertex shader
			PROJECT_DIR + std::string("/game/shaders/cube.frag") // fragment shader
	);

	glm::vec3 cube_positions[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (int i = 0; i < 10; i++)
	{
		auto cube = Cube();
		cube.SetShader(cube_shader);
		cube.AddTexture(wood_texture);
		cube.AddTexture(smiley_texture);

		cube.SetWorldLocation(cube_positions[i].x, cube_positions[i].y, cube_positions[i].z);

		cube.SetWorldRotation(20.0f * i, -20.0f * i, 0.0f);

		engine->Register(cube);
	}

//	engine->ToggleWireframe();

	// Render the registered actors
	engine->Render();
}
