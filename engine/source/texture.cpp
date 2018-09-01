#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

Texture2D::Texture2D(const GLubyte* image_data, int width, int height, int num_channels)
{
	// Load the texture file
	if (image_data)
	{
		// Define the configurations
		// TODO(Ahura Jami): Allow user to set these configurations
		data.width = width;
		data.height = height;
		data.num_channels = num_channels;
		data.wrap_s = GL_REPEAT;
		data.wrap_t = GL_REPEAT;
		data.filter_min = GL_LINEAR;
		data.filter_mag = GL_LINEAR;
		data.internal_format = GL_RGB;
		data.image_format = data.num_channels == 3 ? GL_RGB : GL_RGBA;

		// Generate texture object from the image_data with defined configuration
		GenerateTexture2D(image_data);
	}
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}


void Texture2D::GenerateTexture2D(const GLubyte* image_data)
{
	// Generate the texture
	glGenTextures(1, &id);

	// Bind the generated texture so that any subsequent command can configure it
	glBindTexture(GL_TEXTURE_2D, id);

	// Generate a texture using the loaded image data
	glTexImage2D(GL_TEXTURE_2D,
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
}



