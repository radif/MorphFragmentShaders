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

void main()
{
    
    
    vec2 uv = v_texCoord-0.5;
    float angle = atan(uv.y,uv.x);
    float radius = length(uv);
    angle+= radius*u_time*4.0;
    vec2 shifted = radius*vec2(cos(angle), sin(angle));
    gl_FragColor = texture2D(u_texture, (shifted+0.5));
    
    
        
}