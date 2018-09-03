#version 330 core

in vec2 texture_coordinates;

out vec4 frag_color;

// The fragment shader should also have access to the texture object
// Call glBindTexture(GL_TEXTURE_2D, texture_name) before calling the draw function
// and OpenGL will automatically bind it to this unfirom sampler2D
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    frag_color = mix(
                texture(texture0, texture_coordinates),
                texture(texture1, texture_coordinates),
                0.2);
}