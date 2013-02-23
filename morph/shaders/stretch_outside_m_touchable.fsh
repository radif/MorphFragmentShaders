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

vec2 relativeDistance(vec2 touchPontInverted){
    //moving towards the touch point with influence
    vec2 relativeDistance=touchPontInverted-v_texCoord;
    relativeDistance=relativeDistance*.3;
    
    return relativeDistance;
}

float influence(vec2 touchPont){
    //how far from the touch point?
    float distance=distance(v_texCoord, touchPont);
    
    //how much influence?
    float temp=(distance*.5) *PI-PI*.5;
    return cos(temp/**bulgeRatio*/)*bulgeRatio;
}

void main()
{
    
    
    vec2 touchPont1Inverted=vec2(1.0-u_touch1PosX, 1.0-u_touch1PosY);
    vec2 touchPont1=vec2(u_touch1PosX, u_touch1PosY);
    
    vec2 touchPont2Inverted=vec2(1.0-u_touch2PosX, 1.0-u_touch2PosY);
    vec2 touchPont2=vec2(u_touch2PosX, u_touch2PosY);
    
    //returning texture if no touches detected
    if(touchPont1==undefVec && touchPont2==undefVec){
        gl_FragColor = texture2D(u_texture, v_texCoord).rgba;
        return;
    }
    
    bool doubleTouch=true;
    //making one touch equal another one if
    if(touchPont1==undefVec){
        touchPont1=touchPont2;
        touchPont1Inverted=touchPont2Inverted;
        doubleTouch=false;
    }else if(touchPont2==undefVec)
        doubleTouch=false;
    

    vec2 coords=v_texCoord;

    if (doubleTouch){
        vec2 relativeDistance1=relativeDistance(touchPont1Inverted);
        vec2 relativeDistance2=relativeDistance(touchPont2Inverted);
        
        coords=coords-relativeDistance1*influence(touchPont1)+relativeDistance1;
        coords=coords-relativeDistance2*influence(touchPont2)+relativeDistance2;
    }else{
        vec2 relativeDistance1=relativeDistance(touchPont1Inverted);
        coords=coords-relativeDistance1*influence(touchPont1)+relativeDistance1;
    }
    //removing the mirroring, assuming there is a transparent channel around
    coords.x=clamp(coords.x, 0.0, 1.0);
    coords.y=clamp(coords.y, 0.0, 1.0);
    gl_FragColor = texture2D(u_texture, fract(vec2(coords.x, coords.y))).rgba;

    
}