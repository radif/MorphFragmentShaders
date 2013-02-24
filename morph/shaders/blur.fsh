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


float blurRad = 0.0075;

float blurredColorChannel(int channelIndex){
    float colorChannel = 0.0;
    
    //Sample texture colors in 9x9 grid
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x - blurRad, v_texCoord.y + blurRad))[channelIndex] * 0.05;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y + blurRad))[channelIndex] * 0.14;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x + blurRad, v_texCoord.y + blurRad))[channelIndex] * 0.05;
    
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x - blurRad, v_texCoord.y))[channelIndex] * 0.14;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y))[channelIndex] *0.24;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x + blurRad, v_texCoord.y))[channelIndex] * 0.14;
    
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x - blurRad, v_texCoord.y - blurRad))[channelIndex] * 0.05;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y - blurRad))[channelIndex] * 0.14;
    colorChannel += texture2D(u_texture, vec2(v_texCoord.x + blurRad, v_texCoord.y - blurRad))[channelIndex] * 0.05;
    
    return colorChannel;
}

void main()
{
    
    gl_FragColor= vec4(
                       blurredColorChannel(0),
                       blurredColorChannel(1),
                       blurredColorChannel(2),
                       blurredColorChannel(3)
    );
    
    
}