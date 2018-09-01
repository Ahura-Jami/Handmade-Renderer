#include "texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include <iostream>
#include <texture.h>

TextureInfo::~TextureInfo()
{
	std::cout << "Texture info destroyed" << std::endl;

	stbi_image_free(data);
}


Texture::Texture(const std::string &texture_path)
{
	// Load the texture file
	TextureInfo texture_info;
	LoadTextureFile(texture_path, &texture_info);

	// Generate texture object
	texture = GenerateTexture2D(texture_info);
}


void Texture::LoadTextureFile(const std::string& texture_path, TextureInfo* texture_info) const
{
	// flip the y access to comply with OpenGL representation
	stbi_set_flip_vertically_on_load(true);

	// Load the texture file
	texture_info->data = stbi_load(
			texture_path.c_str(),
			&texture_info->width,
			&texture_info->height,
			&texture_info->num_channels,
			0);

	if (not texture_info->data)
	{
		std::cout << "Error: Failed loading texture file: " << texture_path << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}
}


GLuint Texture::GenerateTexture2D(const TextureInfo& texture_info)
{
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

	// Generate a texture using the loaded image data
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			texture_info.width,
			texture_info.height,
			0,
			texture_info.num_channels == 3 ? GL_RGB : GL_RGBA,
			GL_UNSIGNED_BYTE,
			texture_info.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

