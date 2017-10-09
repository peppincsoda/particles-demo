// FRAGMENT SHADER
#version 330

uniform sampler2D gDiffuseMap;

in vec2 TexCoord;
in vec4 f_Color;

void main(void)
{
    vec4 diffuse = texture2D(gDiffuseMap, TexCoord).rgba;
//    if (diffuse.r == 0.0 && diffuse.g == 0.0 && diffuse.b == 0.0)
//        discard;
    gl_FragColor = diffuse * f_Color;
}
