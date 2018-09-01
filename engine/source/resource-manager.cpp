#include "resource-manager.h"

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stb/stb_image.h>


std::map<std::string, Shader>& ResourceManager::GetShaderRegistry()
{
	static std::map<std::string, Shader> shaders;
	return shaders;
}


std::map<std::string, Texture2D>& ResourceManager::GetTextureRegistry()
{
	static std::map<std::string, Texture2D> textures;
	return textures;
}


Shader ResourceManager::LoadShader(const std::string& name,
								   const std::string& vertex_shader_path,
								   const std::string& fragment_shader_path,
								   const std::string& geometry_shader_path)
{
	// Read vertex and fragment shaders files
	std::string vertex_code = ReadShaderFile(vertex_shader_path.c_str());
	std::string fragment_code = ReadShaderFile(fragment_shader_path.c_str());

	// Read geometry shader file if given
	std::string geometry_code;
	if (not geometry_shader_path.empty())
	{
		geometry_code = ReadShaderFile(geometry_shader_path.c_str());
	}

	// Create a shader object and store it in the shader registry
	auto shader = Shader(vertex_code, fragment_code, geometry_code);
	GetShaderRegistry()[name] = shader;

	// Return the newly created shader
	return shader;
}


std::string ResourceManager::ReadShaderFile(const GLchar* shader_path)
{
	// shader code to be filled and returned
	std::string shader_code;

	// Retrieve the shader source from the input file path
	std::ifstream shader_file;

	// ensure ifstream objects can throw exceptions
	shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		shader_file.open(shader_path);

		// Read file's buffer contents into the stream
		std::stringstream shader_string_stream;
		shader_string_stream << shader_file.rdbuf();

		// close file handler
		shader_file.close();

		// convert stream into string
		shader_code = shader_string_stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FAILED_READING_FILE" << std::endl;
		std::cout << "error: failed reading the file: " << shader_path << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}

	// Return the shader_code
	return shader_code;
}


Shader ResourceManager::GetShader(const std::string& name)
{
	return GetShaderRegistry()[name];
}


Texture2D ResourceManager::LoadTexture(const std::string& name, const std::string& file/*, GLboolean alpha*/)
{
	// Read the input texture file and load its data
	int width, height, num_channels;
	GLubyte* image_data = ReadTextureFile(file, &width, &height, &num_channels);

	// Create a texture object and store it in the texture registry
	auto texture = Texture2D(image_data, width, height, num_channels);
	GetTextureRegistry()[name] = texture;

	// free the image data as they are bound to the texture and are no longer needed in this form
	stbi_image_free(image_data);

	// Return the newly created texture object
	return texture;
}


GLubyte* ResourceManager::ReadTextureFile(const std::string& file, int* width, int* height, int* num_channels)
{
	// flip the y access to comply with OpenGL representation
	stbi_set_flip_vertically_on_load(true);

	// Load the texture file
	GLubyte* image_data = stbi_load(file.c_str(), width, height, num_channels, 0);

	if (not image_data)
	{
		std::cout << "Error: Failed loading texture file: " << file << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}

	return image_data;
}


Texture2D ResourceManager::GetTexture(const std::string& name)
{
	return GetTextureRegistry()[name];
}


void ResourceManager::Clear()
{
	// delete all shaders
	for (auto& shader : GetShaderRegistry())
	{
		glDeleteProgram(shader.second.id);
	}

	// delete all textures
	for (auto& texture : GetTextureRegistry())
	{
		glDeleteTextures(1, &texture.second.id);
	}
}

