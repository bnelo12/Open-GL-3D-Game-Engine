//
//  Plane.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/3/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Plane.hpp"

Plane::Plane(Material material) {
    this->material = new Material(material);
    init();
}

Plane::Plane(std::vector<Texture*> lightingMaps) {
    this->hasTextureMaps = true;
    for (auto &tex : lightingMaps) {
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

void Plane::init() {
    vertexData = {
    //  verticies           UVS             Normal
        -1.0f, 0.0f,-1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 0.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 0.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
    };
    Primitive::init();
}
