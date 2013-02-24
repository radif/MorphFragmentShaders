//Radif Sharafullin
//radif.sharafullin(at)gmail.com

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;
varying vec2 v_texCoord;
uniform float u_time;

//random function
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec4 m_color=texture2D(u_texture, v_texCoord).rgba;


    if(m_color.a<.1){
        gl_FragColor = m_color;
        return;
    }

    float r, g;
    float t=u_time;
    
    lowp int tint=int(t);
    
    
    if (t>1.)
        t-=float(tint);
    t*=2.;
    
    if (t>1.)
        t=2.-t;
    
    t+=1.;
    r=rand(v_texCoord-t*t);
    g=rand(v_texCoord+t*t*t);
    float color=max(r,g);
    gl_FragColor = vec4(color,color,color,1);
    
}
