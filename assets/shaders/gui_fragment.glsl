#version 330 core

const float cornerSmoothFactor = 0.55;

// inputs
in vec2 textureCoord;

// outputs
out vec4 FragColor;

// uniforms
uniform sampler2D u_texture;
uniform vec4 u_color;
uniform vec2 u_size; // size of the gui box
uniform float u_radius; // round u_radius
uniform int u_round_corners;

float square(float val) {
	return val * val;
}

float distanceSquared(vec2 p1, vec2 p2) {
	vec2 vector = p2 - p1;
	return dot(vector, vector);
}

float round_corners() {
	if (u_radius <= 0.0) {
		return 1.0;
	}
	vec2 pixel_pos = textureCoord * u_size;
	vec2 mix_corners = vec2(u_radius, u_radius);
	vec2 max_corner = vec2(u_size.x - u_radius, u_size.y - u_radius);

	vec2 corner_point = clamp(pixel_pos, mix_corners, max_corner);
	float lower_bound = square(u_radius - cornerSmoothFactor);
	float upper_bound = square(u_radius + cornerSmoothFactor);
	return smoothstep(upper_bound, lower_bound, distanceSquared(pixel_pos, corner_point));
}

void main()
{
    vec4 color = u_color;
    
    if (u_round_corners == 1) {
		color.a *= round_corners(); // looks sexy when we round them tbh
	}

	FragColor = vec4(1, 1, 1, texture(u_texture, textureCoord).r) * color; // color * texture(u_texture, textureCoord);
}
