#include <iostream>
#include <memory>
#include <cstring>

#include "engine.h"
#include "stb/stb_image.h"

#include "triangle.h"
#include "rectangle.h"

int main()
{
	// Create the Engine object
	auto engine = std::make_unique<Engine>();

	// Initialize the engine
	if (!engine->Init())
		return -1;

	// Load the shaders
	std::string vertex_path = std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.vert";
	std::string fragment_path = std::string(PROJECT_DIR) + "/game/shaders/triangle_shader.frag";
	Shader triangle_shader = Shader(vertex_path.c_str(), fragment_path.c_str());

	// Generate the texture
	GLuint texture;
	glGenTextures(1, &texture);

	// Bind the generated texture so that any subsequent command can configure it
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set the texture wrapping/filtering options for the currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the texture
	std::string texture_path = std::string(PROJECT_DIR) + "/game/textures/wooden-container.jpg";
	int width, height, num_channels;
	GLubyte* texture_data = stbi_load(texture_path.c_str(), &width, &height, &num_channels, 0);

	if (texture_data)
	{
		// Generate a texture using the loaded image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error: Failed loading texture file: " << texture_path << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}

	// Free the image memory
	stbi_image_free(texture_data);

	// Create triangle
	// Define vertices and their appropriate data
	float triangle_vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.5f, 1.0f  // top
	};
	auto triangle = Triangle(triangle_vertices, triangle_shader);

	// Pass the texture to the triangle
	triangle.SetTexture(texture);
	engine->Register(triangle);

	// Create rectangle
	float rectangle_vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	auto rectangle = Rectangle(rectangle_vertices, triangle_shader);
	rectangle.SetTexture(texture);
	engine->Register(rectangle);

	// Enable wireframe mode
//	engine->ToggleWireframe();

	// Render the registered actors
	engine->Render();
}
