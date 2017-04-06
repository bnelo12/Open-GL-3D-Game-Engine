#version 410

uniform mat4 model;
uniform mat4 camera;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UVCoord;

out vec2 fragUVCoord;

void main() {
    fragUVCoord = vec2(UVCoord.x, 1-UVCoord.y);
    gl_Position = camera*model*vec4(vert, 1);
}
