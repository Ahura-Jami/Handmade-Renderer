#include "texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include <iostream>
#include <texture.h>

Texture2D::Texture2D(const std::string &texture_path)
{
	// Load the texture file
	if (GLubyte* image_data = LoadTextureFile(texture_path))
	{
		// Define the configurations
		// TODO(Ahura Jami): Allow user to set these configurations
		data.wrap_s = GL_REPEAT;
		data.wrap_t = GL_REPEAT;
		data.filter_min = GL_LINEAR;
		data.filter_mag = GL_LINEAR;
		data.internal_format = GL_RGB;
		data.image_format = data.num_channels == 3 ? GL_RGB : GL_RGBA;

		// Generate texture object from the image_data with defined configuration
		id = GenerateTexture2D(image_data);

		// free the image data as they are bound to the texture and are no longer needed in this form
		stbi_image_free(image_data);
	}
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

GLubyte* Texture2D::LoadTextureFile(const std::string& texture_path)
{
	// flip the y access to comply with OpenGL representation
	stbi_set_flip_vertically_on_load(true);

	// Load the texture file
	GLubyte* image_data = stbi_load(
			texture_path.c_str(),
			&data.width,
			&data.height,
			&data.num_channels,
			0);

	if (not image_data)
	{
		std::cout << "Error: Failed loading texture file: " << texture_path << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}

	return image_data;
}


GLuint Texture2D::GenerateTexture2D(const GLubyte* image_data)
{
	// Generate the texture
	GLuint texture;

	glGenTextures(1, &texture);

	// Bind the generated texture so that any subsequent command can configure it
	glBindTexture(GL_TEXTURE_2D, texture);

	// Generate a texture using the loaded image data
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			data.internal_format,
			data.width,
			data.height,
			0,
			data.image_format,
			GL_UNSIGNED_BYTE,
			image_data);

	// Generate minmap of the texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set the texture wrapping/filtering options for the currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, data.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, data.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, data.filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, data.filter_mag);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}



