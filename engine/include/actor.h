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
	void AddTexture(const std::shared_ptr<Texture2D> &texture_ptr)
	{
		texture.emplace_back(texture_ptr);
	}

	void SetShader(const std::shared_ptr<Shader>& shader_ptr)
	{
		shader = shader_ptr;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};

	std::vector<std::shared_ptr<Texture2D>> texture;

	std::shared_ptr<Shader> shader;

	std::function<void()> draw_function;
};

#endif //ENGINE_ACTOR_H
