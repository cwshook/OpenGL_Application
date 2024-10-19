#version 330 core

in vec3 vertex_color;
in vec2 texture_coords;

out vec4 frag_color;

void main(void) {
        gl_FragColor = vec4(vertex_color, 1.0);
}
