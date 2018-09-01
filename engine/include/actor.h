#ifndef ENGINE_ACTOR_H
#define ENGINE_ACTOR_H

#include <glad/glad.h>
#include <functional>
#include <memory>

#include "shader.h"
#include "texture.h"

class Actor
{
public:
	Actor() = default;

	/**
	 * Transfer the ownership of the texture to
	 * @param in_texture 
	 * @param actor 
	 */
	void SetTexture(const std::shared_ptr<Texture>& texture_ptr)
	{
		texture = texture_ptr;
	}

	void SetShader(const std::shared_ptr<Shader>& shader_ptr)
	{
		shader = shader_ptr;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};

	std::shared_ptr<Texture> texture;

	std::shared_ptr<Shader> shader;

	std::function<void()> draw_function;
};

#endif //ENGINE_ACTOR_H
