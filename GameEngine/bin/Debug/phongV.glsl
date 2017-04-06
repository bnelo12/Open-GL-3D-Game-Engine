#version 410

uniform mat4 model;
uniform mat4 camera;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UVCoord;

out vec2 fragUVCoord;
out vec3 fragNormal;
out vec3 fragVert;

void main() {
    fragUVCoord = vec2(UVCoord.x, 1-UVCoord.y);
    fragNormal = mat3(transpose(inverse(model))) * normal;
    fragVert = vec3(model*vec4(vert, 1));
    gl_Position = camera*model*vec4(vert, 1);
}
