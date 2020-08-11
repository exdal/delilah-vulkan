#version 330 core

// inputs
in vec2 textureCoord;

// outputs
out vec4 FragColor;

// uniforms
uniform sampler2D u_texture;
uniform vec4 u_color;

void main()
{
    FragColor = u_color * texture(u_texture, textureCoord);
}
