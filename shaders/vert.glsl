#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

layout (location = 0) out vec2 texCoords;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);

void main() {
    gl_Position = u_Proj * u_Model * vec4(pos, 0.0, 1.0);
    texCoords = uv;
}