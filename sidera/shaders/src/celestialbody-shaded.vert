#version 450

//per instance
layout (location = 0) in float x_parameter;
layout (location = 1) in float y_parameter;
layout (location = 2) in float z_parameter;
layout (location = 3) in float color_filter_data;

layout (location = 0) out vec4  body_position;
layout (location = 1) out vec4  body_fragment_position;
layout (location = 2) out float body_color_filter_data;

layout (push_constant) uniform _pconst {
    mat4 projection;
    mat4 view;//camera view matrix with contains parameters types
} pconst;

#define GAIA_VIEW_PARAMETER_TYPE_RA                   0.0
#define GAIA_VIEW_PARAMETER_TYPE_DEC                  1.0
#define GAIA_VIEW_PARAMETER_TYPE_BARYCENTRIC_DISTANCE 2.0
#define GAIA_OTHER_VIEW_PARAMETER_TYPE                3.0

vec4 triangle[3] = vec4[3](
    vec4(-1.0, 1.0, 0.0, 1.0),
	vec4( 0.0,-1.0, 0.0, 1.0),
	vec4( 1.0, 1.0, 0.0, 1.0)
);



#define GAIA_VIEW_MODE_CARTESIAN 0.0
#define GAIA_VIEW_MODE_POLAR     1.0



void main() {

     mat4 view = pconst.view;

    //GET PARAMETERS TYPES FROM VIEW RULES MATRIX
    //
    //
    float view_mode = view[0][3];//row 0 column 3

    //RESET VIEW RULES TO STANDARD VIEW MATRIX
    //
    //
    view[0][3] = 0.0;

    //CHECK VIEW PARAMETERS
    //
    //
    if (
        view_mode == GAIA_VIEW_MODE_CARTESIAN
    ) {
        body_position = vec4(1.0);//on purpose vec4(1.0)
        body_position.x = x_parameter;
        body_position.y =-y_parameter;
        body_position.z = z_parameter;
    }
    
    //EXCEPTION: PROJECT STARS
    //
    //
    else if (
        view_mode == GAIA_VIEW_MODE_POLAR
    ) {
        float asc  = x_parameter;
        float dec  = y_parameter;
        float dist = z_parameter;
        body_position = vec4(
            dist * sin(dec) * cos(asc), 
            dist * sin(dec) * sin(asc), 
            dist * cos(dec), 
            1.0
        );
    }

    body_color_filter_data = color_filter_data;

    //VIEW MATRIX CORRECTION
    //
    //
    //view[0][0] = 1.0; 
    //view[0][1] = 0.0; 
    //view[0][2] = 0.0; 
    //view[1][0] = 0.0; 
    //view[1][1] = 1.0; 
    //view[1][2] = 0.0; 
    //view[2][0] = 0.0; 
    //view[2][1] = 0.0; 
    //view[2][2] = 1.0;

    vec4 mesh_vertex_position = vec4(triangle[gl_VertexIndex % 3] * 2.0f);

    body_fragment_position = vec4(triangle[gl_VertexIndex % 3].xyz * 2.0f + body_position.xyz, 1.0f);


    vec4 view_pos        = view * vec4(body_position.xyz, 1.0f);
    vec4 vertex_position = pconst.projection * (view_pos + vec4(mesh_vertex_position.xy,0,0));
    gl_Position          = vertex_position;

}