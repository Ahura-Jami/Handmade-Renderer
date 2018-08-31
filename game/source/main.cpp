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

	// Create a custom 2d triangle actor
	auto triangle = Triangle();

	// Register the triangle for engine to draw
	engine->Register(triangle);

//	// Create and register the custom 2D rectangle
//	auto rectangle = Rectangle();
//	engine->Register(rectangle);

	// Enable wireframe mode
	engine->ToggleWireframe();


	// Render the registered actors
	engine->Render();
}
