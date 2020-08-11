#version 330 core

layout (location = 0) in vec2 iPos;
layout (location = 1) in vec2 iTextureCoord;

// out
out vec2 textureCoord;

// uniforms
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
    textureCoord = iTextureCoord;
	gl_Position = u_projection * u_view * u_model * vec4(iPos, 0.0, 1.0);
}