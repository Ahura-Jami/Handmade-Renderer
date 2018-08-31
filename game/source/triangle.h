#ifndef ENGINE_TRIANGLE_H
#define ENGINE_TRIANGLE_H

#include <iostream>
#include <vector>

#include "actor.h"

class Triangle : public Actor
{
public:
	Triangle(const float* in_vertices)
	{
		for (int i = 0; i < 9; ++i)
		{
			vertices[i] = in_vertices[i];
		}

		Create();
	}

	~Triangle() = default;

private:
	void Create()
	{
		// Bind a vertex array object to store the soon to be defined configuration of
		// vertex attribute
		glGenVertexArrays(1, &vertex_array_object);

		// Generate a vertex buffer object to send a chunk of data at once to the GPU memory
		GLuint vertex_buffer_object;
		glGenBuffers(1, &vertex_buffer_object);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
		// configure vertex attributes(s).
		glBindVertexArray(vertex_array_object);

		// Bind the created buffer object to a buffer type target
		// For the case of simple vertices, we need a buffer type of GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

		// Copy the vertices' data into the buffer object
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Tell OpenGL how to interpret vertex data
		// @NOTE: These two functions need to be called before binding a new buffer and
		//		  not necessarily before releasing the currently bound buffer.
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Exercise 1
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Release the buffer target
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the vertex_array_object so other vertex_array_object calls won't accidentally modify this vertex_array_object, but this rarely happens.
		// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind
		// VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// populate draw function
		draw_function = []()
		{
//			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Exercise 1
			glDrawArrays(GL_TRIANGLES, 0, 6);
		};

		// vertex shader source code
		// TODO(Ahura Jami): Move to a separate file.
		const GLchar* vertex_shader_source =
				"#version 330 core\n"
				"layout (location = 0) in vec3 pos;\n"
				"void main()\n"
				"{\n"
				"	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
				"}\0";

		// Create an empty shader object
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

		// Attach the source code to the newly created empty shader object
		glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);

		// Compile the vertex shader
		glCompileShader(vertex_shader);

		// Check whether the compilation was successfull
		GLint success;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar info_log[512];
			glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
		}

		// Fragment shader
		// TODO(Ahura Jami): Move to a separate file.
		const GLchar* fragment_shader_source =
				"#version 330 core\n"
				"out vec4 frag_color;\n"
				"void main()\n"
				"{\n"
				"	frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\n\0";

		// Create and compile the fragment shader just like above vertex shader
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar info_log[512];
			glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
		}

		// Link the compiled shaders into a shader program that can be used for rendering
		// 1. Create shader program
		shader_program = glCreateProgram();

		// 2. Attach the compiled shaders to the program
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);

		// 3. Link the attached shaders to each other
		glLinkProgram(shader_program);

		// Check if the linking was successfull
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar info_log[512];
			glGetProgramInfoLog(fragment_shader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
		}

		// Delete the created shaders as they're no longer needed (since they're
		// already compiled and linked to the program).
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

private:
	/**
	* Vertex input in normalized device coordinates [-1, 1]
	*/
	float vertices[9];
};

#endif //ENGINE_TRIANGLE_H
