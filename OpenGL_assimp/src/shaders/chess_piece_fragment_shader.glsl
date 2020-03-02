#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

// Directional light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform DirLight dirLight;  
uniform Material material;

uniform vec3 viewPos;
uniform samplerCube skybox;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(FragPos - viewPos);

    vec3 lightDir = normalize(-dirLight.direction);
    // Diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(viewDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient = dirLight.ambient  * material.diffuse;
    //vec3 diffuse  = dirLight.diffuse  * diff * material.diffuse;
    vec3 diffuse = texture(skybox, reflectDir).rgb;
    vec3 specular = dirLight.specular * spec * material.specular;
    FragColor = vec4((diffuse), 1.0f);
}