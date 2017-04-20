#version 410

uniform samplerCube cubemap;

in vec3 textureDir;

out vec4 colour;

void main()
{
    colour = texture(cubemap, textureDir);
}
