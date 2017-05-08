//
//  Mesh.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/11/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures) {
    for (int i = 0; i <  vertices.size(); i++) {
        vertexData.insert(vertexData.end(), {
            vertices[i].position.x, vertices[i].position.y, vertices[i].position.z,
            vertices[i].uv.x, vertices[i].uv.y,
            vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z
        });
    }
    this->indicies = indices;
    this->hasTextureMaps  = true;
    for (auto &tex : textures) {
        switch (tex->type) {
            case MAP::DIFFUSE:
                this->diffuseMap = tex;
                break;
            case MAP::SPECULAR:
                this->specularMap = tex;
                break;
            case MAP::EMISSION:
                this->emissionMap = tex;
                break;
        }
    }
    init();
}

void Mesh::init() {
    glGenBuffers(1, &this->EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicies.size() * sizeof(GLuint),
                 &this->indicies[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    Primitive::init();
}
