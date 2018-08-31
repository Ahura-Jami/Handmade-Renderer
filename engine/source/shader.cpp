#include "shader.h"

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <shader.h>

Shader::Shader(const GLchar *vertex_path, const GLchar *fragment_path)
{
	// Read vertex and fragment shaders files
	std::string vertex_code = ReadShaderFile(vertex_path);
	std::string fragment_code = ReadShaderFile(fragment_path);

	// Create and compile vertex and fragment shaders
	GLuint vertex = CreateAndCompileShader(GL_VERTEX_SHADER, vertex_code);
	GLuint fragment = CreateAndCompileShader(GL_FRAGMENT_SHADER, fragment_code);

	// Link shaders to the class member "shader_program"
	shader_program = LinkShaders(vertex, fragment);

	// Delete the shaders as they're linked into our program now and are no longer needed.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


std::string Shader::ReadShaderFile(const GLchar *shader_path) const
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
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
	}

	// Return the shader_code
	return shader_code;
}


GLuint Shader::CreateAndCompileShader(GLenum shader_type, const std::string &shader_code) const
{
	// Create the shader
	GLuint shader = glCreateShader(shader_type);

	// Add the source code to the newly created shader
	const GLchar* shader_code_c_str = shader_code.c_str();
	glShaderSource(shader, 1, &shader_code_c_str, NULL);

	// compile the shader
	glCompileShader(shader);

	// print compile errors if any
	int success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(not success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	// return the reference to the created and compiled shader
	return shader;
}


GLuint Shader::LinkShaders(GLuint vertex, GLuint fragment)
{
	// Create the shader program
	GLuint program = glCreateProgram();

	// attach and link the vertex and fragment shaders
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	// print linking errors if any
	int success;
	char info_log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (not success)
	{
		glGetProgramInfoLog(program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	// return the reference to the created shader program
	return program;
}


void Shader::Use()
{
	glUseProgram(shader_program);
}


void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(shader_program, name.c_str()), static_cast<int>(value));
}


void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}


void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
}

