#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

Shader::Shader(const std::string& vertex_code,
			   const std::string& fragment_code,
			   const std::string& geometry_code)
{
	// Create and compile vertex and fragment shaders
	GLuint vertex = CreateAndCompileShader(GL_VERTEX_SHADER, vertex_code);
	GLuint fragment = CreateAndCompileShader(GL_FRAGMENT_SHADER, fragment_code);

	// Create and compile geometry shader if given
	if (not geometry_code.empty())
	{
		GLuint geometry = CreateAndCompileShader(GL_GEOMETRY_SHADER, geometry_code);

		// link all 3 shaders to the program
		id = LinkShaders(vertex, fragment, geometry);

		// Delete the geometry shader here
		glDeleteShader(geometry);
	}
	else
	{
		// no geometry shader provided, just link vertex and fragment shaders to the program
		id = LinkShaders(vertex, fragment);
	}

	// Delete the shaders as they're linked into our program now and are no longer needed.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::Use()
{
	glUseProgram(id);
//	return *this;
}


GLuint Shader::CreateAndCompileShader(GLenum shader_type, const std::string &shader_code) const
{
	// Get the name of the shader base on the input shader type to be used for error checking
	std::string shader_type_str;
	switch(shader_type)
	{
		default:
		{
			std::cout << "Invalid input shader type." << std::endl;
			return 0;
		}
		case GL_VERTEX_SHADER:
		{
			shader_type_str = "VERTEX";
			break;
		}
		case GL_FRAGMENT_SHADER:
		{
			shader_type_str = "FRAGMENT";
			break;
		}
		case GL_GEOMETRY_SHADER:
		{
			shader_type_str = "GEOMETRY";
		}
	}

	// Create the shader
	GLuint shader = glCreateShader(shader_type);

	// Add the source code to the newly created shader
	const GLchar* shader_code_c_str = shader_code.c_str();
	glShaderSource(shader, 1, &shader_code_c_str, NULL);

	// compile the shader
	glCompileShader(shader);

	// Check for compile errors if any

	CheckCompileOrLinkErrors(shader, shader_type_str);

	// return the reference to the created and compiled shader
	return shader;
}


GLuint Shader::LinkShaders(GLuint vertex, GLuint fragment, GLuint geometry) const
{
	// Create the shader program
	GLuint program = glCreateProgram();

	// attach and link the vertex and fragment shaders
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	if (geometry != 0)
	{
		glAttachShader(program, geometry);
	}

	glLinkProgram(program);

	// print linking errors if any
	CheckCompileOrLinkErrors(program, "PROGRAM");

	// return the reference to the created shader program
	return program;
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


void Shader::SetBool(const GLchar* name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}


void Shader::SetInteger(const GLchar* name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name), value);
}


void Shader::SetFloat(const GLchar* name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name), value);
}
