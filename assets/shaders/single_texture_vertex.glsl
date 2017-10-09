// VERTEX SHADER
#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_TexCoord;

uniform mat4 gWorldViewProj;

out vec2 TexCoord;

void main(void)
{
    gl_Position = gWorldViewProj * vec4(in_Position, 1.0);
    TexCoord = in_TexCoord;
}
