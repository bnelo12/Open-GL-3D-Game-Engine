#version 410

uniform vec3 cameraPos;

//Material
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

//Light
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

//Texture Maps
uniform bool hasDiffuseTextureMap;

uniform sampler2D diffuse_map;

in vec2 fragUVCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main() {
    
    //Ambient
    vec3 ambientCoefficient = material.ambient*light.ambient;
    
    //Diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(light.position - fragVert);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseCoefficient = (diff*material.diffuse)*light.diffuse;
    
    //Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - fragVert);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (spec*material.specular)*light.specular;
    
    vec4 fragColour;
    if (hasDiffuseTextureMap) {
        fragColour = texture(diffuse_map, fragUVCoord);
    } else {
        fragColour = vec4(1,1,1,1);
    }
    
    finalColor =  vec4((ambientCoefficient+diffuseCoefficient+specular), fragColour.a);
}
