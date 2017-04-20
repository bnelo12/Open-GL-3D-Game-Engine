//
//  SkyBox.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/19/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "SkyBox.hpp"

SkyBox::SkyBox(CubeMap* map) {
    this->map = map;
    init();
}

void SkyBox::init() {
    vector<GLfloat> vertexData = {
        -1.f,-1.f,-1.f,
        1.f,-1.f,-1.f,
        -1.f,-1.f, 1.f,
        1.f,-1.f,-1.f,
        1.f,-1.f, 1.f,
        -1.f,-1.f, 1.f,
        
        // top
        -1.f, 1.f,-1.f,
        -1.f, 1.f, 1.f,
        1.f, 1.f,-1.f,
        1.f, 1.f,-1.f,
        -1.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        
        // front
        -1.f,-1.f, 1.f,
        1.f,-1.f, 1.f,
        -1.f, 1.f, 1.f,
        1.f,-1.f, 1.f,
        1.f, 1.f, 1.f,
        -1.f, 1.f, 1.f,
        
        // back
        -1.f,-1.f,-1.f,
        -1.f, 1.f,-1.f,
        1.f,-1.f,-1.f,
        1.f,-1.f,-1.f,
        -1.f, 1.f,-1.f,
        1.f, 1.f,-1.f,
        
        // left
        -1.f,-1.f, 1.f,
        -1.f, 1.f,-1.f,
        -1.f,-1.f,-1.f,
        -1.f,-1.f, 1.f,
        -1.f, 1.f, 1.f,
        -1.f, 1.f,-1.f,
        
        // right
        1.f,-1.f, 1.f,
        1.f,-1.f,-1.f,
        1.f, 1.f,-1.f,
        1.f,-1.f, 1.f,
        1.f, 1.f,-1.f,
        1.f, 1.f, 1.f

    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GL_FLOAT), &vertexData[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*)0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SkyBox::render() {
    glDepthMask(GL_FALSE);
    glUseProgram(Program::SKY_BOX);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, map->textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}
