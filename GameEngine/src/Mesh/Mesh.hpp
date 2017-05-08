//
//  Mesh.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/11/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>

#include "Texture.hpp"
#include "Material.hpp"
#include "Program.hpp"
#include "Primitive.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace glm;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
};

class Mesh : public Primitive {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures);
private:
    void init();

};

#endif /* Mesh_hpp */
