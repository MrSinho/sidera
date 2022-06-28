#version 450

flat    layout (location = 0) in vec4  body_position;
        layout (location = 1) in vec4  fragment_position;
        layout (location = 2) in float teff;

layout (location = 0) out vec4 fragColor;

layout (set = 1, binding = 0) uniform uniformBuffer {
    vec4 camera_position;
} ubo;

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

float kelvin_table_t[111] = float[111]( 1000.0f, 1100.0f, 1200.0f, 1300.0f, 1400.0f, 1500.0f, 1600.0f, 1700.0f, 1800.0f, 1900.0f, 2000.0f, 2100.0f, 2200.0f, 2300.0f, 2400.0f, 2500.0f, 2600.0f, 2700.0f, 2800.0f, 2900.0f, 3000.0f, 3100.0f, 3200.0f, 3300.0f, 3400.0f, 3500.0f, 3600.0f, 3700.0f, 3800.0f, 3900.0f, 4000.0f, 4100.0f, 4200.0f, 4300.0f, 4400.0f, 4500.0f, 4600.0f, 4700.0f, 4800.0f, 4900.0f, 5000.0f, 5100.0f, 5200.0f, 5300.0f, 5400.0f, 5500.0f, 5600.0f, 5700.0f, 5800.0f, 5900.0f, 6000.0f, 6100.0f, 6200.0f, 6300.0f, 6400.0f, 6500.0f, 6600.0f, 6700.0f, 6800.0f, 6900.0f, 7000.0f, 7100.0f, 7200.0f, 7300.0f, 7400.0f, 7500.0f, 7600.0f, 7700.0f, 7800.0f, 7900.0f, 8000.0f, 8100.0f, 8200.0f, 8300.0f, 8400.0f, 8500.0f, 8600.0f, 8700.0f, 8800.0f, 8900.0f, 9000.0f, 9100.0f, 9200.0f, 9300.0f, 9400.0f, 9500.0f, 9600.0f, 9700.0f, 9800.0f, 9900.0f, 1000.0f, 1010.0f, 1020.0f, 1030.0f, 1040.0f, 1050.0f, 1060.0f, 1070.0f, 1080.0f, 1090.0f, 1100.0f, 1110.0f, 1120.0f, 1130.0f, 1140.0f, 1150.0f, 1160.0f, 1170.0f, 1180.0f, 1190.0f, 1200.0f );

mat4 saturateColor(float saturation) {
    vec3 luminance = vec3( 0.3086f, 0.6094f, 0.0820f );
    
    float oneMinusSat = 1.0f - saturation;
    
    vec3 red = vec3( luminance.x * oneMinusSat );
    red+= vec3( saturation, 0.0f, 0.0f );
    
    vec3 green = vec3( luminance.y * oneMinusSat );
    green += vec3( 0.0f, saturation, 0.0f );
    
    vec3 blue = vec3( luminance.z * oneMinusSat );
    blue += vec3( 0.0f, 0.0f, saturation );
    
    return mat4( red,     0.0f,
                 green,   0.0f,
                 blue,    0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f );
}

vec4 starColor(vec4 temperature_color, float k) {
    float r = distance(fragment_position, body_position);
    if (r > 0.5f) {
        discard;
    }
    float fact = k / r - 0.75f;
    return vec4(vec3(normalize(temperature_color.xyz) * fact), 1.0f * fact);
}

void main() {

    vec4 temperature_color = vec4(1.0);
    for (uint i = 0; i < 110; i++) {
        if (teff >= kelvin_table_t[i] && teff <= kelvin_table_t[i+1]) {
            temperature_color = (kelvin_table_rgb[i] + kelvin_table_rgb[i+1]) / 2.0f;
            break;
        }
    }
    

    fragColor = saturateColor(4.0) *
                starColor(temperature_color, 0.9f) /
                //teff / 
                25.0f;
                //pow(distance(vec4(ubo.camera_position.xyz, 1.0f), fragment_position), 2) * 10.0f;
    
    //fragColor = vec4(1.0f);
}