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
const float PI =  3.14159265;


void main()
{
    //returning texture if no touches detected
    if(u_touch1PosX==-1.0 && u_touch1PosY==-1.0){
        gl_FragColor = texture2D(u_texture, v_texCoord).rgba;
        return;
    }

    vec2 touchPontInverted=vec2(1.0-u_touch1PosX, 1.0-u_touch1PosY);
    vec2 touchPont=vec2(u_touch1PosX, u_touch1PosY);
    //how far from the touch point?
    float distance=distance(v_texCoord, touchPont);
    
    //how much influence?
    float influence=cos((distance) *PI-PI*.5);//traction and bulging
    
    
    //copy the current coords
    vec2 coords=v_texCoord;
    
    //moving towards the touch point with influence
    vec2 relativeDistance=touchPontInverted-coords;
    relativeDistance=relativeDistance*.3;
    //influence=1.0;
    coords=coords-relativeDistance*influence;
    
    //removing the mirroring, assuming there is a transparent channel around
    coords.x=clamp(coords.x, 0.0, 1.0);
    coords.y=clamp(coords.y, 0.0, 1.0);
    
    gl_FragColor = texture2D(u_texture, fract(vec2(coords.x, coords.y))).rgba;
}