#version 330 core

uniform vec3 object_color;

uniform vec3 light_color;


void main()
{
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    vec3 result = ambient * object_color;

	gl_FragColor = vec4(result, 1.0);
}
