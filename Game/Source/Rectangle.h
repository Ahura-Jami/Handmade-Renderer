#ifndef ENGINE_RECTANGLE_H
#define ENGINE_RECTANGLE_H

#include <iostream>

#include "Actor.h"

class Rectangle : public Actor
{
public:
	Rectangle(const float* in_vertices)
	{
		for (int i = 0; i < 32; ++i)
		{
			vertices[i] = in_vertices[i];
		}

		Create();
	}

	~Rectangle() = default;

private:
	void Create()
	{
		// Index drawing - we can draw a rectangle using two triangles and only 4 vertices.
		// Vertex input in normalized device coordinates [-1, 1]

		// indices of the vertices that form the two separate triangles.
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Color attributes
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture attributes
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

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
	}

private:
	/**
	 * Container holding vertices coordinates, their corresponding color and texture coordinates
	 * A rectangle has 4 vertices, each vertex has 3 coordinates xyz, 3 color values rgb, 2 texture values st
	 * => 32 = 4 * (3 + 3 + 2);
	*/
	float vertices[32];
};


#endif //ENGINE_RECTANGLE_H
