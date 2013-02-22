#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform float u_time;

uniform float u_touchPosX;
uniform float u_touchPosY;

const float bendFactor = 0.4;
const float PI =  3.14159265;


void main()
{

    vec2 touchPont=vec2(u_touchPosX, u_touchPosY);
    //how far from the touch point?
    float distance=distance(v_texCoord, touchPont);
    
    //how much influence?
    //float influence=(1.0-distance)/4.0;//linear
    //float influence=cos((1.0-distance) *PI*.8);//bulging
    //float influence=cos((distance) *PI*.8);//reverse bulging
    float influence=cos((distance) *PI-PI*.5);//traction and bulging


    //copy the current coords
    vec2 coords=v_texCoord;

    //moving towards the touch point with influence
    vec2 relativeDistance=touchPont-coords;
    
    //influence=1.0;
    coords=coords-relativeDistance*influence;
    
    //removing the mirroring, assuming there is a transparent channel around
    coords.x=clamp(coords.x, 0.0, 1.0);
    coords.y=clamp(coords.y, 0.0, 1.0);
    
    gl_FragColor = texture2D(u_texture, fract(vec2(coords.x, coords.y))).rgba;
}