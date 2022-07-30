#version 460 core

layout (location = 0) in vec2 texCoords;

layout (location = 0) out vec4 color;

uniform sampler2D tex;

void main() {
    // color = vec4(1.0f, 0.0f, 0.0f, 0.0f);
    color = texture(tex, texCoords);
}