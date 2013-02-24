#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform float u_time;

uniform float u_touch1PosX;
uniform float u_touch1PosY;

uniform float u_touch2PosX;
uniform float u_touch2PosY;

const float PI =  3.14159265;

const float bulgeRatio =  1.4;

const float undefValue = -1.0;
const vec2 undefVec = vec2(-1.0,-1.0);


void main()
{
    
    vec4 color = texture2D(u_texture, v_texCoord).rgba;
    float luminosity=color.r*.299+color.g* .587 +color.b *.114;
    color.r=luminosity;
    color.g=luminosity;
    color.b=luminosity;

    gl_FragColor=color;

    
    
}