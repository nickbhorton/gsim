#version 330 core

in vec3 color;

uniform vec2 u_resolution;
uniform float u_time;

void main() {
    gl_FragColor = vec4(color, 1.0);
}