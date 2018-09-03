#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include "glm/glm.hpp"

// TODO(Ahura): Move to its own Rotator class (Or to a general container class)

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;

struct Rotator
{
	Rotator() = default;

	Rotator(float yaw, float pitch, float roll)
		: yaw(yaw)
		, pitch(pitch)
		, roll(roll)
	{}

	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
};

enum class InputKey
{
	W,
	A,
	S,
	D
};

#endif //ENGINE_TYPES_H
