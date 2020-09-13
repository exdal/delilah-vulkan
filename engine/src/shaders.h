#pragma once

namespace shaders {
    const char *main_vertex = R"~~(
#version 330 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTextureCoord;
layout (location = 3) in float iTextureIndex;
layout (location = 4) in float iTiling;

// out
out vec4 color;
out vec2 textureCoord;
out float textureIndex;
out float tiling;

// uniforms
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
    color = iColor;
    textureCoord = iTextureCoord;
    textureIndex = iTextureIndex;
	tiling = iTiling;
	gl_Position = u_projection * u_view * vec4(iPos, 1.0);
}
)~~";    
    
    const char *main_fragment = R"~~(
#version 330 core

// inputs
in vec4 color;
in vec2 textureCoord;
in float textureIndex;
in float tiling;

// outputs
out vec4 FragColor;

// uniforms
uniform sampler2D u_texture[32];

void main()
{
	vec4 texColor = color;
	switch(int(textureIndex))
	{
		case 0:  texColor *= texture2D(u_texture[0],  textureCoord * tiling); break;
		case 1:  texColor *= texture2D(u_texture[1],  textureCoord * tiling); break;
		case 2:  texColor *= texture2D(u_texture[2],  textureCoord * tiling); break;
		case 3:  texColor *= texture2D(u_texture[3],  textureCoord * tiling); break;
		case 4:  texColor *= texture2D(u_texture[4],  textureCoord * tiling); break;
		case 5:  texColor *= texture2D(u_texture[5],  textureCoord * tiling); break;
		case 6:  texColor *= texture2D(u_texture[6],  textureCoord * tiling); break;
		case 7:  texColor *= texture2D(u_texture[7],  textureCoord * tiling); break;
		case 8:  texColor *= texture2D(u_texture[8],  textureCoord * tiling); break;
		case 9:  texColor *= texture2D(u_texture[9],  textureCoord * tiling); break;
		case 10: texColor *= texture2D(u_texture[10], textureCoord * tiling); break;
		case 11: texColor *= texture2D(u_texture[11], textureCoord * tiling); break;
		case 12: texColor *= texture2D(u_texture[12], textureCoord * tiling); break;
		case 13: texColor *= texture2D(u_texture[13], textureCoord * tiling); break;
		case 14: texColor *= texture2D(u_texture[14], textureCoord * tiling); break;
		case 15: texColor *= texture2D(u_texture[15], textureCoord * tiling); break;
		case 16: texColor *= texture2D(u_texture[16], textureCoord * tiling); break;
		case 17: texColor *= texture2D(u_texture[17], textureCoord * tiling); break;
		case 18: texColor *= texture2D(u_texture[18], textureCoord * tiling); break;
		case 19: texColor *= texture2D(u_texture[19], textureCoord * tiling); break;
		case 20: texColor *= texture2D(u_texture[20], textureCoord * tiling); break;
		case 21: texColor *= texture2D(u_texture[21], textureCoord * tiling); break;
		case 22: texColor *= texture2D(u_texture[22], textureCoord * tiling); break;
		case 23: texColor *= texture2D(u_texture[23], textureCoord * tiling); break;
		case 24: texColor *= texture2D(u_texture[24], textureCoord * tiling); break;
		case 25: texColor *= texture2D(u_texture[25], textureCoord * tiling); break;
		case 26: texColor *= texture2D(u_texture[26], textureCoord * tiling); break;
		case 27: texColor *= texture2D(u_texture[27], textureCoord * tiling); break;
		case 28: texColor *= texture2D(u_texture[28], textureCoord * tiling); break;
		case 29: texColor *= texture2D(u_texture[29], textureCoord * tiling); break;
		case 30: texColor *= texture2D(u_texture[30], textureCoord * tiling); break;
		case 31: texColor *= texture2D(u_texture[31], textureCoord * tiling); break;
	}
    FragColor = texColor;
}
)~~";

	const char *blur_v = R"~~(
#version 330 core

layout (location = 0) in vec3 iPos;

out vec3 pos;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	pos = iPos;
	gl_Position = u_projection * u_view * vec4(iPos, 1.0);
}
)~~";

		const char *blur_f = R"~~(
#version 330 core

in vec3 pos;

out vec4 FragColor;

uniform vec2 u_blur_res;
uniform sampler2D u_texture;
uniform vec2 direction;

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += texture2D(image, uv) * 0.1964825501511404;
  color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;
  color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;
  return color;
}

void main()
{
	vec2 uv = vec2(pos.xy / u_blur_res.xy);
	FragColor = blur13(u_texture, uv, u_blur_res, direction);
}
)~~";
}