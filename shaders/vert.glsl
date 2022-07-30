#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

layout (location = 0) out vec2 texCoords;

uniform mat4 u_Model;

void main() {
    gl_Position = u_Model * vec4(pos, 0.0, 1.0);
    texCoords = uv;
}