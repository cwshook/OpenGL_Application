#version 330 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 textures;

out vec3 vertex_color;
out vec2 texture_coords;

void main(void) {
        gl_Position = vec4(vertices, 1.0);
        vertex_color = vec3(vertices + 0.5);
        texture_coords = textures;
}
