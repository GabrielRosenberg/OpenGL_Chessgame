#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 projection;

void main()
{
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));

    vs_out.Normal = aNormal * mat3(transpose(inverse(model)));

   vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)));
   vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
   vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)));
   if (dot(cross(N, T), B) < 0.0)
         T = T * -1.0;
   mat3 TBN = transpose(mat3(T, B, N));
   
   vs_out.TangentLightPos = TBN * lightPos;
   vs_out.TangentViewPos  = TBN * viewPos;
   vs_out.TangentFragPos  = TBN * vec3(model * vec4(aPos, 0.0));
    
   gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}