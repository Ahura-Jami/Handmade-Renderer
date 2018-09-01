#version 330 core

in vec3 color;
in vec2 texture_coordinates;

out vec4 frag_color;

// The fragment shader should also have access to the texture object
// Call glBindTexture(GL_TEXTURE_2D, texture_name) before calling the draw function
// and OpenGL will automatically bind it to this unfirom sampler2D
uniform sampler2D our_texture;

void main()
{
    frag_color = texture(our_texture, texture_coordinates);
}