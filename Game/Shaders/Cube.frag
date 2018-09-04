#version 330 core

in vec3 fragment_position;
in vec3 normal;
in vec2 texture_coordinates;
in vec3 light_position;

// The fragment shader should also have access to the texture object
// Call glBindTexture(GL_TEXTURE_2D, texture_name) before calling the draw function
// and OpenGL will automatically bind it to this unfirom sampler2D
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 light_color;

void main()
{
    vec4 object_color = mix(
                texture(texture0, texture_coordinates),
                texture(texture1, texture_coordinates),
                0.2);

    // add some ambient lighting
    float ambient_strength = 0.1;
    vec3 ambient = light_color * ambient_strength;

    // diffuse lighting
    vec3 light_direction = normalize(light_position - fragment_position);

    // If the angle between both vectors is greater than 90 degrees then the result of the
    // dot product will actually become negative and we end up with a negative diffuse component.
    // For that reason we use the max function that returns the highest of both its parameters
    // to make sure the diffuse component (and thus the colors) never become negative.
    float diffuse_strength = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = diffuse_strength * light_color;

    // specular lighting
    float specular_intesity = 0.5;
    vec3 view_direction = normalize(-fragment_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 64);
    vec3 specular = specular_intesity * spec * light_color;

    gl_FragColor = vec4(ambient + diffuse + specular, 1.0) * object_color;
}