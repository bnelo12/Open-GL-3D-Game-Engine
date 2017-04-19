//
//  Tile.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/16/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(std::vector<Texture*> lightingMaps, int radius) {
    this->hasTextureMaps = true;
    this->radius = radius;
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

void Tile::init() {
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            vertexData.insert(vertexData.end(), {
                -5.0f+i*10.0f, 0.0f,-5.0f+j*10.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                -5.0f+i*10.0f, 0.0f, 5.0f+j*10.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
                5.0f+i*10.0f, 0.0f,-5.0f+j*10.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                5.0f+i*10.0f, 0.0f,-5.0f+j*10.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                -5.0f+i*10.0f, 0.0f, 5.0f+j*10.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
                5.0f+i*10.0f, 0.0f, 5.0f+j*10.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f
            });
        }
    }
    Primitive::init();
}
