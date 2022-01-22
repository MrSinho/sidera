#version 450

layout (location = 0) in float asc;
layout (location = 1) in float dec;
layout (location = 2) in float baricentric_distance;
layout (location = 3) in float teff;
layout (location = 4) in float radius;

layout (location = 0) out vec4 bodyPosition;

void main() {
    mat4 model = mat4(
        -1.0, 0.0, 0.0, 0.0,
         0.0,-1.0, 0.0, 0.0,
         0.0, 0.0,-1.0, 0.0,
         0.0, 0.0, 0.0, 1.0
    );
    gl_PointSize = 5.0;
    
    bodyPosition = vec4(
        baricentric_distance * sin(dec) * cos(asc), 
        baricentric_distance * sin(dec) * sin(asc), 
        baricentric_distance * cos(dec), 
        1.0);
    gl_Position = bodyPosition;
}