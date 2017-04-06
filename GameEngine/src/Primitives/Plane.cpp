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
