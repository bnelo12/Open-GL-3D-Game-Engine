#version 410

uniform mat4 camera;

layout (location = 0) in vec3 vert;

out vec3 textureDir;

void main()
{
    textureDir = vert;
    gl_Position =   camera * vec4(vert, 1.0);
}
