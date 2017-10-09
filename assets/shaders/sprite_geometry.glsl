// GEOMETRY SHADER
#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 Rotation[];
in vec2 Size[];
in vec4 Color[];

out vec2 TexCoord;
out vec4 f_Color;

uniform mat4 gViewProj;
uniform vec3 gEyePos;

void main()
{
    vec4 position = gl_in[0].gl_Position;

    vec3 c = cos(Rotation[0]);
    vec3 s = sin(Rotation[0]);

    mat3 rotation_x = mat3(1.0, 0.0,  0.0,
                           0.0, c.x, -s.x,
                           0.0, s.x,  c.x);

    mat3 rotation_y = mat3( c.y, 0.0, s.y,
                            0.0, 1.0, 0.0,
                           -s.y, 0.0, c.y);

    mat3 rotation_z = mat3(c.z, -s.z, 0.0,
                           s.z,  c.z, 0.0,
                           0.0,  0.0, 1.0);

    mat3 rotation = rotation_z * rotation_y * rotation_x;

    vec2 half_size = Size[0] / 2.0;


    vec3 local_z = normalize(gEyePos - position.xyz);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 local_x = normalize(cross(up, local_z));
    vec3 local_y = normalize(cross(local_z, local_x));
    mat3 local = mat3(local_x, local_y, local_z);

    mat4 translate_to_position = mat4(1.0);
    translate_to_position[3].xyz = position.xyz;

    mat4 transform = gViewProj * translate_to_position * mat4(local * rotation);

    gl_Position = transform * vec4(-half_size.x, -half_size.y, 0.0, 1.0);
    TexCoord = vec2(0.0, 0.0);
    f_Color = Color[0];
    EmitVertex();
    gl_Position = transform * vec4(-half_size.x, +half_size.y, 0.0, 1.0);
    TexCoord = vec2(0.0, 1.0);
    f_Color = Color[0];
    EmitVertex();
    gl_Position = transform * vec4(+half_size.x, -half_size.y, 0.0, 1.0);
    TexCoord = vec2(1.0, 0.0);
    f_Color = Color[0];
    EmitVertex();
    gl_Position = transform * vec4(+half_size.x, +half_size.y, 0.0, 1.0);
    TexCoord = vec2(1.0, 1.0);
    f_Color = Color[0];
    EmitVertex();

    EndPrimitive();
}
