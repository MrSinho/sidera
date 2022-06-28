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

    mat4 view  = pconst.view;
    
    view[0][0] = 1.0; 
    view[0][1] = 0.0; 
    view[0][2] = 0.0; 
    view[1][0] = 0.0; 
    view[1][1] = 1.0; 
    view[1][2] = 0.0; 
    view[2][0] = 0.0; 
    view[2][1] = 0.0; 
    view[2][2] = 1.0;

    //vec4 vertex_position = vec4(triangle[gl_VertexIndex % 3] * 2.0f + body_position.xyz, 1.0f);
    vec4 mesh_vertex_position = vec4(triangle[gl_VertexIndex % 3] * 2.0f, 1.0f);
    //vertex_position = view * vertex_position;
    //fragment_position = vertex_position;
//
    //gl_Position = pconst.projection * vertex_position;

    vec4 view_pos = pconst.view * vec4(body_position.xyz, 1.0f);
    vec4 vertex_position = pconst.projection * (view_pos + vec4(mesh_vertex_position.xy,0,0));
    gl_Position = vertex_position;
    fragment_position = vec4(triangle[gl_VertexIndex % 3] * 2.0f + body_position.xyz, 1.0f);
    

}