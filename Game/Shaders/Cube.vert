#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coordinates;
layout (location = 2) in vec3 in_normal;

out vec3 fragment_position;
out vec3 normal;
out vec2 texture_coordinates;
out vec3 light_position;

uniform vec3 in_light_position;
//uniform mat4 model;
uniform mat4 view;
uniform mat4 model_view;
uniform mat4 model_view_projection;

void main()
{
	gl_Position = model_view_projection * vec4(in_position, 1.0);

	texture_coordinates = in_texture_coordinates;

	// transform fragment_position to view-space
	fragment_position = vec3(model_view * vec4(in_position, 1.0));

	// TODO(Ahura): Inversing matrices is a costly operation even for shaders so wherever possible, try to avoid doing inverse operations in shaders since they have to be done on each vertex of your scene. For learning purposes this is fine, but for an efficient application you'll likely want to calculate the normal matrix on the CPU and send it to the shaders via a uniform before drawing (just like the model matrix).
	normal = normalize(mat3(transpose(inverse(model_view))) * in_normal);

    // Transform world-space light position to view-space light position
	light_position = vec3(view * vec4(in_light_position, 1.0));
}