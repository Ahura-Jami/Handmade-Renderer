#ifndef ENGINE_ACTOR_H
#define ENGINE_ACTOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "Types.h"

class Actor
{
public:
	Actor() = default;

	virtual void Tick(float delta_time) {};

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

	void SetWorldRotation(float yaw, float pitch, float roll)
	{
		world_rotation.yaw = yaw;
		world_rotation.pitch = pitch;
		world_rotation.roll = roll;
	}

	void SetWorldScale(float x, float y, float z)
	{
		world_scale.x = x;
		world_scale.y = y;
		world_scale.z = z;
	}

	glm::mat4 GetModelMatrix() const
	{
		glm::mat4 model_mat = glm::mat4(1.0f);
		model_mat = glm::translate(model_mat, world_location);

		// TODO(Ahura): This may result in Gimbal lock. Implement quaternions instead.
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.yaw), glm::vec3(1.0f, 0.0f, 0.0f));
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.pitch), glm::vec3(0.0f, 1.0f, 0.0f));
		model_mat = glm::rotate(model_mat, glm::radians(world_rotation.roll), glm::vec3(0.0f, 0.0f, 1.0f));

		model_mat = glm::scale(model_mat, world_scale);

		return model_mat;
	}

	GLuint vertex_array_object{};
	GLuint vertex_buffer_object{};
	GLuint element_buffer_object{};

	std::vector<Texture2D> textures{};

	Shader shader;

	std::function<void()> draw_function;

	glm::vec3 world_location = glm::vec3(0.0f);
	Rotator world_rotation = Rotator(0.0f, 0.0f, 0.0f);
	glm::vec3 world_scale = glm::vec3(1.0f);
};

#endif //ENGINE_ACTOR_H
