#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform float u_time;

uniform float u_touchPosX;
uniform float u_touchPosY;


const float speed = 2.0;
const float bendFactor = 0.2;

const float waveRadius=0.01;
const float timeAcceleration=15.0;

void main()
{

    float stepVal=(u_time *timeAcceleration)+v_texCoord.x*61.8;
    float offset=cos(stepVal)*waveRadius;
    
    gl_FragColor = texture2D(u_texture, fract(vec2(v_texCoord.x, v_texCoord.y+offset))).rgba;
}