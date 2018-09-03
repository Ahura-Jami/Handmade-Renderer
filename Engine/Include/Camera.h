#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Actor.h"
#include "Types.h"


class Camera : public Actor
{
public:
	Camera();

	~Camera();

	void Tick(float delta_time) override;

	void ProcessMouseMovement(Vector2 mouse_position);

	void Zoom(double amount);

	// TODO (Ahura): Move to a controller class
	// TODO(Ahura): Find a better way to process inputs that would not require GLFWwindow as argument
	void MoveForward(InputKey key, float delta_time);
	void MoveRight(InputKey key, float delta_time);

public:
	float GetCurrentFieldOfView() const { return current_field_of_view; }
	float GetFieldOfView() const { return field_of_view; }
	void SetFieldOfView(const float fov) { field_of_view = fov; }

	const glm::mat4& GetViewMatrix() const { return view_matrix; }

	float GetSpeed() const { return speed; }
	void SetSpeed(const float speed) { this->speed = speed; }

	float GetNearPlane() const { return near_plane; }
	float SetNearPlane(float value) { near_plane = value; }

	float GetFarPlane() const { return far_plane; }
	float SetFarPlane(float value) { far_plane = value; }

private:
	Vector3 position = Vector3(0.0f, 0.0f, 3.0f);
	Rotator rotation = Rotator(-90.0f, 0.0f, 0.0f);

	Vector3 front_axis = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up_axis = Vector3(0.0f, 1.0f, 0.0f);

	float field_of_view = 45.0f;
	float current_field_of_view = 45.0f;

	// TODO(Ahura) Move the control functionalities to a Controller class
	Vector2 last_mouse_position = Vector2(0.0f, 0.0f);

	bool first_mouse = true;

	float speed = 2.5f;

	glm::mat4 view_matrix = glm::mat4(1.0f);

	float near_plane = 0.1f;
	float far_plane = 100.0f;
};


#endif //ENGINE_CAMERA_H
