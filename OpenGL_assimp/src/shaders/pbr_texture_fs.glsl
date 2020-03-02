#version 330 core
#define M_PI 3.1415926535897932384626433832795

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal;
} vs_out;

uniform struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    float shininess;
} material;

uniform float metallic;
uniform float roughness;
uniform float ao;

vec3 fresnelSchlick(float cosTheta, vec3 F0);
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);



void main() {    

    vec3 albedo = pow(texture(material.texture_diffuse1, vs_out.TexCoords).rgb, vec3(2.2));
    vec3 normal = texture(material.texture_normal1, vs_out.TexCoords).rgb;
    vec3 N = normalize(normal * 2.0 - 1.0);  

    vec3 lightColor = vec3(1.0);

    vec3 V = normalize(vs_out.TangentViewPos - vs_out.TangentFragPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);

    // For-loop here 

    vec3 L = normalize(vs_out.TangentLightPos - vs_out.TangentFragPos);
    vec3 H = normalize(V + L);

    float distance = length(vs_out.TangentLightPos - vs_out.TangentFragPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    float NDF = DistributionGGX(N, H, roughness);       
    float G = GeometrySmith(N, V, L, roughness);   
    vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

    vec3 nominator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular = nominator / max(denominator, 0.001); 

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    float NdotL = max(dot(N, L), 0.0);        
    Lo += (kD * albedo / M_PI + specular) * radiance * NdotL;
    
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color   = ambient + Lo; 

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);

}

// Shader functions
// ----------------

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - min(cosTheta, 1.0), 0.5);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = M_PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}