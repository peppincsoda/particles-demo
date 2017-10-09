// FRAGMENT SHADER
#version 330

in vec4 Color;

void main(void)
{
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    gl_FragColor = Color;
}
