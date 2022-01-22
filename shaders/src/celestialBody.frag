#version 450

layout (location = 0) in vec4 bodyPosition;

layout (location = 0) out vec4 fragColor;

void main() {
    //fragColor = bodyPosition - vec4(0.0, 0.0, 0.0, 1.0);
    fragColor = vec4(1.0);
}