// VERTEX SHADER
#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Rotation;
layout(location = 2) in vec2 in_Size;
layout(location = 3) in vec4 in_Color;

out vec3 Rotation;
out vec2 Size;
out vec4 Color;

void main(void)
{
    gl_Position = vec4(in_Position, 1.0);
    Rotation    = in_Rotation;
    Size        = in_Size;
    Color       = in_Color;
}
