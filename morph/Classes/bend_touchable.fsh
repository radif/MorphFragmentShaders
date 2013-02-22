#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform float u_time;

uniform float u_touchPosX;
uniform float u_touchPosY;

const float bendFactor = 0.4;
void main()
{
    
    float height = 1.0-u_touchPosY - v_texCoord.y;
    float offset = pow(height, 2.5);
    offset *= (sin((1.0-u_touchPosX)*3.14-3.14/2.0) * bendFactor);
    
    //removing the mirroring
    float xCoord=clamp(v_texCoord.x + offset, 0.0, 1.0);
    float yCoord=clamp(v_texCoord.y, 0.0, 1.0);
    
    gl_FragColor = texture2D(u_texture, fract(vec2(xCoord, yCoord))).rgba;
}