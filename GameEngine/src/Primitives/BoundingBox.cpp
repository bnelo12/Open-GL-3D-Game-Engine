//
//  BoundingBox.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 5/8/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "BoundingBox.hpp"
#include <math.h>

BoundingBox::BoundingBox(std::vector<GLfloat> vertices) {
    colour = new vec4(1.f,1.f,0.f,1.f);
    init(maxMag(vertices), minMag(vertices));
}

vec3 BoundingBox::maxMag(std::vector<GLfloat> vertexData) {
    vec3 out = vec3(0);
    for (int i = 0; i < vertexData.size(); i += 8) {
        if (vertexData[i] > out.x) out.x = vertexData[i];
        if (vertexData[i+1] > out.y) out.y = vertexData[i+1];
        if (vertexData[i+2] > out.z) out.z = vertexData[i+2];
    }
    return out;
}

vec3 BoundingBox::minMag(std::vector<GLfloat> vertexData) {
    vec3 out = vec3(0);
    for (int i = 0; i < vertexData.size(); i += 8) {
        if (vertexData[i] < out.x) out.x = vertexData[i];
        if (vertexData[i+1] < out.y) out.y = vertexData[i+1];
        if (vertexData[i+2] < out.z) out.z = vertexData[i+2];
    }
    return out;
}

void BoundingBox::init(vec3 max, vec3 min) {
    vertexData = {
        min.x, min.y, min.z,
        max.x, min.y, min.z,
        max.x, min.y, max.z,
        min.x, min.y, max.z,
        min.x, max.y, min.z,
        max.x, max.y, min.z,
        max.x, max.y, max.z,
        min.x, max.y, max.z
    };
    
    indicies = {
        0,1,
        1,2,
        2,3,
        0,3,
        4,5,
        5,6,
        6,7,
        4,7,
        3,7,
        0,4,
        1,5,
        2,6
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GL_FLOAT), &vertexData[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*)0);
    
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BoundingBox::render() {
    GLuint prog = Program::FLAT;
    glUseProgram(prog);
    
    GLint hasTextureUniform = glGetUniformLocation(prog, "hasDiffuseTextureMap");
    glUniform1i(hasTextureUniform, false);
    
    GLuint modelUniform = glGetUniformLocation(prog, "model");
    glUniformMatrix4fv(modelUniform, 1, false, value_ptr(model));
    
    GLint colourUniform = glGetUniformLocation(prog, "colour");
    glUniform4fv(colourUniform, 1, value_ptr(*this->colour));
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_LINES, (GLsizei)indicies.size(), GL_UNSIGNED_INT, (void*)0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glUseProgram(0);
}
