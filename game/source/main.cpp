#include <iostream>
#include <memory>

#include "engine.h"

#include "triangle.h"
#include "rectangle.h"

int main()
{
	// Create the Engine object
	auto engine = std::make_unique<Engine>();

	// Initialize the engine
	if (!engine->Init())
		return -1;

	// Exercise 2: Create two different triangles
	float v1[] = {
			0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			-0.5f, 0.0f, 0.0f
	};
	auto triangle1 = Triangle(v1);
	engine->Register(triangle1);

	float v2[] = {
			0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.0f,
			0.5f, 0.0f, 0.0f
	};
	auto triangle2 = Triangle(v2);
	engine->Register(triangle2);

	// Create and register the custom 2D rectangle
//	auto rectangle = Rectangle();
//	engine->Register(rectangle);

	// Enable wireframe mode
	engine->ToggleWireframe();


	// Render the registered actors
	engine->Render();
}
