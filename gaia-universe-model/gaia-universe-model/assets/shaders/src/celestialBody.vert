#version 450

layout (location = 0) out vec4  body_position;
layout (location = 1) out vec4  fragment_position;
layout (location = 2) out float body_teff;
layout (location = 3) out float body_radius;

layout (push_constant) uniform pushConstant {
    mat4 projection;
    mat4 view;
} pconst;

layout (set = 0, binding = 0) buffer celestialBodies {
    vec4 asc_dec_distance_teff[];
} bodies;

vec3 triangle[3] = vec3[3](
    vec3(-1.0f, 1.0f, 0.0f),
	vec3( 0.0f,-1.0f, 0.0f),
	vec3( 1.0f, 1.0f, 0.0f)
);

void main() {

    uint body_index = gl_VertexIndex / 3;

    float asc = bodies.asc_dec_distance_teff[body_index].x;
    float dec = bodies.asc_dec_distance_teff[body_index].y;
    float dist = bodies.asc_dec_distance_teff[body_index].z;
    float teff = bodies.asc_dec_distance_teff[body_index].w;
    body_teff = teff;

    body_position = vec4(
        dist * sin(dec) * cos(asc), 
        dist * sin(dec) * sin(asc), 
        dist * cos(dec), 
        1.0
    );


    vec4 vertex_position = vec4(triangle[gl_VertexIndex % 3] * 2.0f + body_position.xyz, 1.0f);

    fragment_position = vertex_position;

    gl_Position = pconst.projection * pconst.view * vertex_position;
}