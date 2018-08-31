#include <iostream>
#include <memory>
#include <cstring>

#include "engine.h"

#include "triangle.h"

int main()
{
	// Create the Engine object
	auto engine = std::make_unique<Engine>();

	// Initialize the engine
	if (!engine->Init())
		return -1;

	float v[] = {
			0.50f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, // bottom left
			0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f  // top
	};

	std::string vertex_path = std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.vert";
	std::string fragment_path = std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.frag";

	Shader triangle_shader = Shader(vertex_path.c_str(), fragment_path.c_str());

	auto triangle = Triangle(v, triangle_shader);

	engine->Register(triangle);

	// Enable wireframe mode
//	engine->ToggleWireframe();

	// Render the registered actors
	engine->Render();
}
