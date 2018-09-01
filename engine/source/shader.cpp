#include "shader.h"

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <shader.h>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
	// Read vertex and fragment shaders files
	std::string vertex_code = ReadShaderFile(vertex_path.c_str());
	std::string fragment_code = ReadShaderFile(fragment_path.c_str());

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
		std::cout << "ERROR::SHADER::FAILED_READING_FILE" << std::endl;
		std::cout << "error: failed reading the file: " << shader_path << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
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

	// Check for compile errors if any
	CheckCompileOrLinkErrors(shader, shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

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
	CheckCompileOrLinkErrors(program, "PROGRAM");

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


void Shader::CheckCompileOrLinkErrors(GLuint shader, const std::string &type) const
{
	int success;
	char infoLog[1024];

	if ("PROGRAM" != type)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR::" << type << "\n" << infoLog;
			std::cout << "--------------------------------------------------------" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
			std::cout << "--------------------------------------------------------" << std::endl;
		}
	}
}
