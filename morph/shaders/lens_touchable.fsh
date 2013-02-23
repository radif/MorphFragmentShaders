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

const float bendFactor = 0.4;


void main()
{

    vec2 touchPont=vec2(u_touch1PosX, u_touch1PosY);
    //how far from the touch point?
    float distance=distance(v_texCoord, touchPont);
    
    //how much influence?
    float influence=1.0-distance;
  

    //copy the current coords
    vec2 coords=v_texCoord;

    //moving towards the touch point with influence
    vec2 relativeDistance=coords-touchPont;
    
    if (distance<.2){
        coords=touchPont-relativeDistance;
    }
    
    
    //removing the mirroring, assuming there is a transparent channel around
    coords.x=clamp(coords.x, 0.0, 1.0);
    coords.y=clamp(coords.y, 0.0, 1.0);
    
    gl_FragColor = texture2D(u_texture, fract(vec2(coords.x, coords.y))).rgba;
}