#ifndef ENGINE_ACTOR_H
#define ENGINE_ACTOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <memory>

#include "shader.h"
#include "texture.h"

class Actor
{
public:
	Actor() = default;

	void Tick(float delta_time)
	{
		world_rotation.x += delta_time * 20.0f;
		world_rotation.y += delta_time * 5.0f;

	}

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

	void SetWorldLocation(float x, float y, float z)
	{
		world_location.x = x;
		world_location.y = y;
		world_location.z = z;
	}

	void SetWorldRotation(float x, float y, float z)
	{
		world_rotation.x = x;
		world_rotation.y = y;
		world_rotation.z = z;
	}

	glm::mat4 GetModelMatrix()
	{
		glm::mat4 model_mat = glm::mat4(1.0f);
		model_mat = glm::translate(model_mat, world_location);

		// TODO(Ahura): This may result in Gimbal lock. Implement quaternions instead.
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model_mat = glm::scale(model_mat, world_scale);

		return model_mat;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};

	std::vector<Texture2D> textures;

	Shader shader;

	std::function<void()> draw_function;

	glm::vec3 world_location = glm::vec3(0.0f);
	glm::vec3 world_rotation = glm::vec3(0.0f);
	glm::vec3 world_scale = glm::vec3(1.0f);
};

#endif //ENGINE_ACTOR_H
