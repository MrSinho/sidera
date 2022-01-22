#version 450

layout (location = 0) in float asc;
layout (location = 1) in float dec;
layout (location = 2) in float baricentric_distance;
layout (location = 3) in float teff;
layout (location = 4) in float radius;

layout (location = 0) out vec4 bodyPosition;

layout (push_constant) uniform pushConstant {
    mat4 projection;
    mat4 view;
} pconst;

void main() {
    gl_PointSize = 1.0;
    float dist = baricentric_distance * 0.01;
    bodyPosition = pconst.projection * pconst.view * vec4(
        dist * sin(dec) * cos(asc), 
        dist * sin(dec) * sin(asc), 
        dist * cos(dec), 
        1.0);
    gl_Position = bodyPosition;
}