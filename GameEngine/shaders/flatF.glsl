#version 410

uniform bool hasDiffuseTextureMap;
uniform vec4 colour;
uniform sampler2D diffuse_map;

in vec2 fragUVCoord;

out vec4 finalColour;

void main() {
    if(hasDiffuseTextureMap) {
        finalColour = texture(diffuse_map, fragUVCoord);
    } else {
        finalColour = colour;
    }
}
