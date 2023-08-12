#version 450

flat layout (location = 0) in vec4  body_position;
     layout (location = 1) in vec4  fragment_position;
flat layout (location = 2) in float color_filter_data;

layout (location = 0) out vec4 frag_color;



//copied from GaiaModelColorFilterType
#define GAIA_MODEL_COLOR_FILTER_TYPE_RANDOM_COLOR_SEED    0
#define GAIA_MODEL_COLOR_FILTER_TYPE_BARICENTRIC_DISTANCE 1
#define GAIA_MODEL_COLOR_FILTER_TYPE_TEFF                 2
#define GAIA_MODEL_COLOR_FILTER_TYPE_LOGG                 3
#define GAIA_MODEL_COLOR_FILTER_TYPE_FEH                  4
#define GAIA_MODEL_COLOR_FILTER_TYPE_ALPHAFE              5
#define GAIA_MODEL_COLOR_FILTER_TYPE_AGE                  6
#define GAIA_MODEL_COLOR_FILTER_TYPE_MASS                 7
#define GAIA_MODEL_COLOR_FILTER_TYPE_RADIUS               8
#define GAIA_MODEL_COLOR_FILTER_TYPE_VSINI                9
#define GAIA_MODEL_COLOR_FILTER_TYPE_MAX_ENUM

//copied from GaiaModelShadeType
#define GAIA_MODEL_SHADE_TYPE_PIXEL          0
#define GAIA_MODEL_SHADE_TYPE_CIRCLE         1
#define GAIA_MODEL_SHADE_TYPE_CLOUD          2
#define GAIA_MODEL_SHADE_TYPE_ANIMATED_CLOUD 3



layout (std140, set = 0, binding = 0) uniform _settings {//static global properties
    int   color_filter_type;
    int   shade_type;
    float time;
} settings;



vec4 kelvin_table_rgb[111] = vec4[111](
    vec4(255.0f/255.0f,  56.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f,  71.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f,  83.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f,  93.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 101.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 109.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 115.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 121.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 126.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 131.0f/255.0f,   0.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 138.0f/255.0f,  18.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 142.0f/255.0f,  33.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 147.0f/255.0f,  44.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 152.0f/255.0f,  54.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 157.0f/255.0f,  63.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 161.0f/255.0f,  72.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 165.0f/255.0f,  79.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 169.0f/255.0f,  87.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 173.0f/255.0f,  94.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 177.0f/255.0f, 101.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 180.0f/255.0f, 107.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 184.0f/255.0f, 114.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 187.0f/255.0f, 120.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 190.0f/255.0f, 126.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 193.0f/255.0f, 132.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 196.0f/255.0f, 137.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 199.0f/255.0f, 143.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 201.0f/255.0f, 148.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 204.0f/255.0f, 153.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 206.0f/255.0f, 159.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 209.0f/255.0f, 163.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 211.0f/255.0f, 168.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 213.0f/255.0f, 173.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 215.0f/255.0f, 177.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 217.0f/255.0f, 182.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 219.0f/255.0f, 186.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 221.0f/255.0f, 190.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 223.0f/255.0f, 194.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 225.0f/255.0f, 198.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 227.0f/255.0f, 202.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 228.0f/255.0f, 206.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 230.0f/255.0f, 210.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 232.0f/255.0f, 213.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 233.0f/255.0f, 217.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 235.0f/255.0f, 220.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 236.0f/255.0f, 224.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 238.0f/255.0f, 227.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 239.0f/255.0f, 230.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 240.0f/255.0f, 233.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 242.0f/255.0f, 236.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 243.0f/255.0f, 239.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 244.0f/255.0f, 242.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 245.0f/255.0f, 245.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 246.0f/255.0f, 247.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 248.0f/255.0f, 251.0f/255.0f, 1.0f),
    vec4(255.0f/255.0f, 249.0f/255.0f, 253.0f/255.0f, 1.0f),
    vec4(254.0f/255.0f, 249.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(252.0f/255.0f, 247.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(249.0f/255.0f, 246.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(247.0f/255.0f, 245.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(245.0f/255.0f, 243.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(243.0f/255.0f, 242.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(240.0f/255.0f, 241.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(239.0f/255.0f, 240.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(237.0f/255.0f, 239.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(235.0f/255.0f, 238.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(233.0f/255.0f, 237.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(231.0f/255.0f, 236.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(230.0f/255.0f, 235.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(228.0f/255.0f, 234.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(227.0f/255.0f, 233.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(225.0f/255.0f, 232.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(224.0f/255.0f, 231.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(222.0f/255.0f, 230.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(221.0f/255.0f, 230.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(220.0f/255.0f, 229.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(218.0f/255.0f, 229.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(217.0f/255.0f, 227.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(216.0f/255.0f, 227.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(215.0f/255.0f, 226.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(214.0f/255.0f, 225.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(212.0f/255.0f, 225.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(211.0f/255.0f, 224.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(210.0f/255.0f, 223.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(209.0f/255.0f, 223.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(208.0f/255.0f, 222.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(207.0f/255.0f, 221.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(207.0f/255.0f, 221.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(206.0f/255.0f, 220.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(205.0f/255.0f, 220.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(207.0f/255.0f, 218.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(207.0f/255.0f, 218.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(206.0f/255.0f, 217.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(205.0f/255.0f, 217.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(204.0f/255.0f, 216.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(204.0f/255.0f, 216.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(203.0f/255.0f, 215.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(202.0f/255.0f, 215.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(202.0f/255.0f, 214.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(201.0f/255.0f, 214.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(200.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(200.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(199.0f/255.0f, 212.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(198.0f/255.0f, 212.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(198.0f/255.0f, 212.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(197.0f/255.0f, 211.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(197.0f/255.0f, 211.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(197.0f/255.0f, 210.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(196.0f/255.0f, 210.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(195.0f/255.0f, 210.0f/255.0f, 255.0f/255.0f, 1.0f),
    vec4(195.0f/255.0f, 209.0f/255.0f, 255.0f/255.0f, 1.0f)
);



float kelvin_table_t[111] = float[111]( 1000.0f, 1100.0f, 1200.0f, 1300.0f, 1400.0f, 1500.0f, 1600.0f, 1700.0f, 1800.0f, 1900.0f, 2000.0f, 2100.0f, 2200.0f, 2300.0f, 2400.0f, 2500.0f, 2600.0f, 2700.0f, 2800.0f, 2900.0f, 3000.0f, 3100.0f, 3200.0f, 3300.0f, 3400.0f, 3500.0f, 3600.0f, 3700.0f, 3800.0f, 3900.0f, 4000.0f, 4100.0f, 4200.0f, 4300.0f, 4400.0f, 4500.0f, 4600.0f, 4700.0f, 4800.0f, 4900.0f, 5000.0f, 5100.0f, 5200.0f, 5300.0f, 5400.0f, 5500.0f, 5600.0f, 5700.0f, 5800.0f, 5900.0f, 6000.0f, 6100.0f, 6200.0f, 6300.0f, 6400.0f, 6500.0f, 6600.0f, 6700.0f, 6800.0f, 6900.0f, 7000.0f, 7100.0f, 7200.0f, 7300.0f, 7400.0f, 7500.0f, 7600.0f, 7700.0f, 7800.0f, 7900.0f, 8000.0f, 8100.0f, 8200.0f, 8300.0f, 8400.0f, 8500.0f, 8600.0f, 8700.0f, 8800.0f, 8900.0f, 9000.0f, 9100.0f, 9200.0f, 9300.0f, 9400.0f, 9500.0f, 9600.0f, 9700.0f, 9800.0f, 9900.0f, 10000.0f, 10100.0f, 10200.0f, 10300.0f, 10400.0f, 10500.0f, 10600.0f, 10700.0f, 10800.0f, 10900.0f, 11000.0f, 11100.0f, 11200.0f, 11300.0f, 11400.0f, 11500.0f, 11600.0f, 11700.0f, 11800.0f, 11900.0f, 12000.0f );



//This code has been taken from somewhere on stackoverflow or shadertoy, I really don't remember...
mat4 saturateColor(float saturation) {
    vec3 luminance = vec3( 0.3086f, 0.6094f, 0.0820f );
    
    float oneMinusSat = 1.0f - saturation;
    
    vec3 red = vec3( luminance.x * oneMinusSat );
    red+= vec3( saturation, 0.0f, 0.0f );
    
    vec3 green = vec3( luminance.y * oneMinusSat );
    green += vec3( 0.0f, saturation, 0.0f );
    
    vec3 blue = vec3( luminance.z * oneMinusSat );
    blue += vec3( 0.0f, 0.0f, saturation );
    
    return mat4( red,     0.0,
                 green,   0.0,
                 blue,    0.0,
                 0.0, 0.0, 0.0, 1.0 );
}

vec4 shade(float r, float saturation, vec4 src_color) {
    float _fact       = 0.9 / r - 2.5;
    vec4  _frag_color = vec4(1.0, 1.0, 0.0, 1.0);//error, yellow
    
    switch(settings.shade_type) {
        case GAIA_MODEL_SHADE_TYPE_PIXEL:
            _frag_color   = saturateColor(saturation) * vec4(normalize(src_color)); 
            _frag_color.w = 1.0;
            break;
        case GAIA_MODEL_SHADE_TYPE_CIRCLE:
            _frag_color   = saturateColor(saturation) * vec4(normalize(src_color)); 
            _frag_color.w = 1.0;
            break;
        case GAIA_MODEL_SHADE_TYPE_CLOUD:
            _frag_color   = saturateColor(saturation) * vec4(normalize(src_color) * _fact) / 5; 
            _frag_color.w = 1.0;
            break;
        case GAIA_MODEL_SHADE_TYPE_ANIMATED_CLOUD:
            _frag_color   = saturateColor(saturation) * vec4(normalize(src_color) * _fact) / 5 - 
                            0.1 * (sin(4 * settings.time + fragment_position.z) + 1);
            _frag_color.w = 1.0;
            break;
        default:
            break;
    }
 
    return _frag_color;
}

vec4 randomize(float r) {
    float _seed               = color_filter_data;
    vec4  _frag_color         = vec4(1.0);

    _frag_color = vec4(
        abs(sin(_seed + 1)),
        abs(sin(_seed + 2)),
        abs(sin(_seed + 3)),
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateBaricentricDistance(float r) {//mag ~= 10^4+
    float _dist               = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 1 * pow(10,-5.0);
    float _green_scale_factor = 1 * pow(10,-1.1);
    float _blue_scale_factor  = 1 * pow(10, 0.4);

    _frag_color = vec4(
        1 / _dist / _red_scale_factor, 
        pow(_dist * _green_scale_factor, 2), 
        _dist * _blue_scale_factor,
        1.0
    );

    return shade(r, 6, _frag_color);
}

vec4 calculateTeff(float r) {//mag ~= 10^3 

    vec4 _temperature_color = vec4(1.0);
    vec4 _frag_color        = vec4(1.0);

    for (uint i = 0; i < 110; i++) {
        if (color_filter_data >= kelvin_table_t[i] && color_filter_data <= kelvin_table_t[i+1]) {
            _temperature_color = (kelvin_table_rgb[i] + kelvin_table_rgb[i+1]) / 2.0f;
            break;
        }
    }

    _temperature_color = shade(r, 6.0, _temperature_color);

    _frag_color = vec4(
                    ( 
                        _temperature_color
                        //pow(distance(vec4(settings.camera_position.xyz, 1.0f), fragment_position), 2) * 10.0f
                    ).xyz,
                    1.0f
                );

    return _frag_color;
}

vec4 calculateLogg(float r) {//mag ~= 10^1
    float _logg               = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 0.6;
    float _green_scale_factor = 0.15;
    float _blue_scale_factor  = 0.15;

    _frag_color = vec4(
        1 / _logg / _red_scale_factor, 
        pow(_logg * _green_scale_factor, 2), 
        _logg * _blue_scale_factor,
        1.0
    );

    return shade(r, 6, _frag_color);
}

vec4 calculateFeH(float r) {//mag ~= 10^-1
    float _feh                = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 1;
    float _green_scale_factor = 0.15;
    float _blue_scale_factor  = 1;

    _frag_color = vec4(
        1 / _feh / _red_scale_factor, 
        pow(_feh * _green_scale_factor, 2), 
        _feh * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateAlphaFe(float r) {////mag ~= 10^-3
    float _alphafe            = abs(color_filter_data);//I don't get it, why some values are negative
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 100;
    float _green_scale_factor = 0.15;
    float _blue_scale_factor  = 1;

    _frag_color = vec4(
        1 / _alphafe / _red_scale_factor,
        pow(_alphafe * _green_scale_factor, 2), 
        _alphafe * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateAge(float r) {////mag ~= 10^1
    float _age                = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 1;
    float _green_scale_factor = 0.35;
    float _blue_scale_factor  = 1; 

    _frag_color = vec4(
        1 / _age / _red_scale_factor,
        pow(_age * _green_scale_factor, 2),
        _age * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateMass(float r) {//mag ~= 10^0
    float _mass                = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 1;
    float _green_scale_factor = 1;
    float _blue_scale_factor  = 1;

    _frag_color = vec4(
        1 / _mass / _red_scale_factor, 
        pow(_mass * _green_scale_factor, 2), 
        _mass * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateRadius(float r) {////mag ~= 10^0
    float _radius             = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 1;
    float _green_scale_factor = 1;
    float _blue_scale_factor  = 1;

    _frag_color = vec4(
        1 / _radius / _red_scale_factor, 
        pow(_radius * _green_scale_factor, 2), 
        _radius * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

vec4 calculateVsini(float r) {//mag ~= 10^0
    float _vsini              = color_filter_data;
    vec4  _frag_color         = vec4(1.0);
    float _red_scale_factor   = 0.4;
    float _green_scale_factor = 0.4;
    float _blue_scale_factor  = 0.6;

    _frag_color = vec4(
        1 / _vsini / _red_scale_factor, 
        pow(_vsini * 0.4, 2), 
        _vsini * _blue_scale_factor,
        1.0
    );

    return shade(r, 3, _frag_color);
}

float discardFragments() {
    float r = distance(fragment_position, body_position);
    if (r > 0.5f) {
        discard;
    }
    return r;
}

//NEED PERFORMANCE IMPROVEMENT__or maybe not___...
//standard (except for teff): red = very_low, blue = very_high (green channel ignored)
void main() {

    float r = discardFragments();

    switch(settings.color_filter_type) {
        case GAIA_MODEL_COLOR_FILTER_TYPE_RANDOM_COLOR_SEED:
            frag_color = randomize(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_BARICENTRIC_DISTANCE:
            frag_color = calculateBaricentricDistance(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_TEFF:
            frag_color = calculateTeff(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_LOGG:
            frag_color = calculateLogg(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_FEH:
            frag_color = calculateFeH(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_ALPHAFE:
            frag_color = calculateAlphaFe(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_AGE:
            frag_color = calculateAge(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_MASS:
            frag_color = calculateMass(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_RADIUS:
            frag_color = calculateRadius(r);
            break;
        case GAIA_MODEL_COLOR_FILTER_TYPE_VSINI:
            frag_color = calculateVsini(r);
            break;
        default:
            frag_color = vec4(0.0, 1.0, 0.0, 1.0);//green used for errors (except for randomness)
    }

    if (length(frag_color) < 1) {
        discard;
    }

    return;
}