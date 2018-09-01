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
	void AddTexture(Texture2D texture)
	{
		this->textures.emplace_back(texture);
	}

	void SetShader(Shader shader)
	{
		this->shader = shader;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};

	std::vector<Texture2D> textures;

	Shader shader;

	std::function<void()> draw_function;
};

#endif //ENGINE_ACTOR_H
