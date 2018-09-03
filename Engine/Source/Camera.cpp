#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Math.h"
#include "Types.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::Tick(float delta_time)
{
	// view axis that must be updated every frame if user changes camera's position/rotation
	view_matrix = glm::lookAt(position, position + front_axis, up_axis);
}

void Camera::MoveForward(InputKey key, float delta_time)
{
	switch (key)
	{
		case InputKey::W:
		{
			position += speed * delta_time * front_axis;
			break;
		}


		case InputKey::S:
		{
			position -= speed * delta_time * front_axis;
			break;
		}
	}

}
	

void Camera::MoveRight(InputKey key, float delta_time)
{
	switch (key)
	{
		case InputKey::A:
		{
			position -= glm::normalize(glm::cross(front_axis, up_axis)) * speed * delta_time;
			break;
		}

		case InputKey::D:
		{
			position += glm::normalize(glm::cross(front_axis, up_axis)) * speed * delta_time;
			break;
		}
	}
}


void Camera::ProcessMouseMovement(glm::vec2 mouse_position)
{
	// 1. calculate the mouse's offset since the last frame
	if(first_mouse)
	{
		last_mouse_position.x = mouse_position.x;
		last_mouse_position.y = mouse_position.y;

		first_mouse = false;
	}

	// calculate the offset movement between the last and current frame
	float offset_x = mouse_position.x - last_mouse_position.x;
	float offset_y = last_mouse_position.y - mouse_position.y;

	// record the new position to be used next time this callback function is called
	last_mouse_position.x = mouse_position.x;
	last_mouse_position.y = mouse_position.y;

	// Lower the offset by a factor of sensitivity to prevent quick and strong mouse movement
	float sensitivity = 0.1f;
	offset_x *= sensitivity;
	offset_y *= sensitivity;

	// 2. Add the offset values to the camera's yaw and pitch values

	// If we don't constrain the yaw to only use values between 0-360
	// we would lose floating precission with very high values, hence
	// the movement would look like big "steps" instead a smooth one!
	rotation.yaw = std::fmod((rotation.yaw + offset_x), 360.0f);

	// Add some constraints to the maximum/minimum pitch values
	rotation.pitch = ClampIntoRange(rotation.pitch + offset_y, -89.0f, 89.0f);

	// 3. Calculate the direction vector
	glm::vec3 front;
	front.x = static_cast<float>(cos(glm::radians(rotation.yaw)) * cos(glm::radians(rotation.pitch)));
	front.y = static_cast<float>(sin(glm::radians(rotation.pitch)));
	front.z = static_cast<float>(sin(glm::radians(rotation.yaw)) * cos(glm::radians(rotation.pitch)));

	front_axis = glm::normalize(front);
}


void Camera::Zoom(double amount)
{
	if (field_of_view >= 1.0f && field_of_view <= 45.0f)
		field_of_view -= amount;

	field_of_view = ClampIntoRange(field_of_view, 1.0f, 45.0f);
}