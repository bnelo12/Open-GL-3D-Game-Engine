#version 410

uniform vec3 cameraPos;

//Light
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D emission_map;

uniform bool hasDiffuseMap;
uniform bool hasSpecularMap;
uniform bool hasEmissionMap;

uniform float emissionStrenth;
uniform vec3 emissionMapColour;

in vec2 fragUVCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main() {
    vec4 emission = vec4(0,0,0,0);
    if(hasEmissionMap) {
        emission = texture(emission_map, fragUVCoord)*vec4(emissionMapColour, 0);
    }
    
    float alpha = texture(diffuse_map, fragUVCoord).a;
    
    //Ambient
    vec3 ambientCoefficient = light.ambient*texture(diffuse_map, fragUVCoord).xyz;
    
    //Diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(light.position - fragVert);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuseCoefficient = vec3(0,0,0);
    if (hasDiffuseMap) {
        diffuseCoefficient = (diff*texture(diffuse_map, fragUVCoord).xyz)*light.diffuse;
    }
        
    //Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - fragVert);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    vec3 specularCoefficient = vec3(0,0,0);
    if(hasSpecularMap) {
        specularCoefficient = (spec*texture(specular_map, fragUVCoord).xyz)*light.specular;
    }
    
    
    finalColor =  vec4(diffuseCoefficient+specularCoefficient+ambientCoefficient,alpha) + emission;
}
