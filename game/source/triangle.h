#ifndef ENGINE_TRIANGLE_H
#define ENGINE_TRIANGLE_H

#include <iostream>
#include <vector>

#include "actor.h"

class Triangle : public Actor
{
public:
	Triangle(const float* in_vertices, Shader in_shader)
	{
		for (int i = 0; i < 24; ++i)
		{
			vertices[i] = in_vertices[i];
		}

		shader = in_shader;

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
		// Vertex layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Color layout
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 2D texture layout
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Release the buffer target
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the vertex_array_object so other vertex_array_object calls won't accidentally modify this vertex_array_object, but this rarely happens.
		// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind
		// VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// populate draw function
		draw_function = []()
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		};
	}

private:
	/**
	 * Container holding vertices coordinates, their corresponding color and texture coordinates
	 * A triangle has 3 vertices, each vertex has 3 coordinates xyz, 3 color values rgb, 2 texture values st
	 * => 24 = 3 * (3 + 3 + 2);
	*/
	float vertices[24]{};

};

#endif //ENGINE_TRIANGLE_H
