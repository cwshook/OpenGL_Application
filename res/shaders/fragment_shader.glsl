#version 330 core

in vec3 vertex_color;
in vec2 texture_coords;

out vec4 frag_color;

uniform sampler2D texture_sampler;

void main(void) {
        frag_color = texture(texture_sampler, texture_coords);
}
