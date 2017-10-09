// FRAGMENT SHADER
#version 330

uniform sampler2D gDiffuseMap;

in vec2 TexCoord;

void main(void)
{
    gl_FragColor = vec4(texture2D(gDiffuseMap, TexCoord).rgb, 1.0);
}
