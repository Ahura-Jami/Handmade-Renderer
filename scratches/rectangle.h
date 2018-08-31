#ifndef ENGINE_RECTANGLE_H
#define ENGINE_RECTANGLE_H

#include <iostream>

#include "actor.h"

class Rectangle : public Actor
{
public:
	Rectangle()
	{
		Create();
	}

	~Rectangle() = default;

private:
	void Create()
	{
		// Index drawing - we can draw a rectangle using two triangles and only 4 vertices.
		// Vertex input in normalized device coordinates [-1, 1]
		float vertices[] = {
				 0.5f,  0.5f, 0.0f, // top right
				 0.5f, -0.5f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f  // top left
		};

		// indices of above vertices that form the two separate triangles.
		unsigned int indices[] = {
				0, 1, 2, // first triangle
				0, 3, 2  // second triangle
		};

		// Bind a vertex array object to store the soon to be defined configuration of vertex attribute
		glGenVertexArrays(1, &vertex_array_object);

		// Generate a vertex buffer object to send a chunk of data at once to the GPU memory
		glGenBuffers(1, &vertex_buffer_object);

		// create an element buffer
		glGenBuffers(1, &element_buffer_object);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
		// configure vertex attributes(s).
		glBindVertexArray(vertex_array_object);

		// 1. Bind the created buffer object to a buffer type target
		// For the case of simple vertices, we need a buffer type of GL_ARRAY_BUFFER
		// 2. Copy the vertices' data into the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 1. Similar to vertex_buffer_object, we bind the element_buffer_object to a buffer type target
		// 2. Copy the indices into the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Tell OpenGL how to interpret vertex data
		// @NOTE: These two functions need to be called before binding a new buffer and
		//		  not necessarily before releasing the currently bound buffer.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Release the buffers
		// @NOTE This is allowed. The call to glVertexAttribPointer registered vertex_buffer_object as the vertex attribute's
		// bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// WARNING: (https://learnopengl.com/Getting-started/Hello-Triangle)
		// A vertex_array_object stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This also means
		// it stores its unbind calls so make sure you don't unbind the element array buffer before unbinding
		// your vertex_array_object, otherwise it doesn't have an element_buffer_object configured.
		//
		// Reminder: do NOT unbind the element_buffer_object while a vertex_array_object is active as the bound element buffer object
		// IS stored in the vertex_array_object; keep the element_buffer_object bound.
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbind the vertex_array_object so other vertex_array_object calls won't accidentally modify this vertex_array_object, but this rarely happens.
		// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind
		// VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// populate draw function
		draw_function = []()
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
};


#endif //ENGINE_RECTANGLE_H
