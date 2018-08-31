#ifndef ENGINE_ACTOR_H
#define ENGINE_ACTOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

class Actor
{
public:
	GLuint vertex_array_object;
	GLuint vertex_buffer_object;
	GLuint element_buffer_object;
	GLuint shader_program;
	std::function<void()> draw_function;
};

#endif //ENGINE_ACTOR_H
