#version 450

layout (location = 0) in float asc;
layout (location = 1) in float dec;
layout (location = 2) in float baricentric_distance;
layout (location = 3) in float teff;

layout (location = 0) out vec4  bodyPosition;
layout (location = 1) out float bodyTeff;
layout (location = 2) out float bodyRadius;

layout (push_constant) uniform pushConstant {
    mat4 projection;
    mat4 view;
} pconst;

#define TRIANGLE_VERTEX_COUNT 12
vec4 triangle[3] = vec4[3](
    vec4(-1.0f, 0.0f, 0.0f, 1.0f),
    vec4( 0.0f,-1.0f, 0.0f, 1.0f),
    vec4( 1.0f,-1.0f, 0.0f, 1.0f)
);

#define DISTANCE_SCALE 0.01

void main() {

    gl_PointSize = 1.0f;
    bodyTeff = teff;

    float dist = baricentric_distance * DISTANCE_SCALE;
    bodyPosition = vec4(
        dist * sin(dec) * cos(asc), 
        dist * sin(dec) * sin(asc), 
        dist * cos(dec), 
        1.0
    );
    gl_Position = pconst.projection * pconst.view * bodyPosition;
}