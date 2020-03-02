#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 ViewPos;
    vec3 LightPos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.Normal = aNormal * mat3(transpose(inverse(model)));
    vs_out.ViewPos = viewPos;
    vs_out.LightPos = lightPos;
}