// VERTEX SHADER
#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;

uniform mat4 gWorldViewProj;

out vec4 Color;

void main(void)
{
    gl_Position = gWorldViewProj * vec4(in_Position, 1.0);
    Color = in_Color;
}
