#ifndef ENGINE_ACTOR_H
#define ENGINE_ACTOR_H

#include <glad/glad.h>
#include <functional>

#include "shader.h"

class Actor
{
public:
	Actor() = default;

	void SetTexture(GLuint in_texture)
	{
		texture = in_texture;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};
	GLuint texture{};
	Shader shader;
	std::function<void()> draw_function;
};

#endif //ENGINE_ACTOR_H
