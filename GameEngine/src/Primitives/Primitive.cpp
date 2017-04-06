//
//  Primitive.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/1/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Primitive.hpp"

void Primitive::init() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GL_FLOAT), &vertexData[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8*sizeof(GL_FLOAT), (GLvoid*)(5*sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8*sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT)));
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (texture) hasDiffuseTextureMap = true;
}

void Primitive::render() {
    GLuint prog = 0;
    
    prog = SHADING_ENABLED ? Program::PHONG : Program::FLAT;
    glUseProgram(prog);
    
    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->textureid);
        GLint diffuseMapUniform = glGetUniformLocation(prog, "diffuse_map");
        glUniform1i(diffuseMapUniform, 0);
    }
    
    if (prog == Program::PHONG) {
        GLint diffuseUniform = glGetUniformLocation(prog, "material.diffuse");
        glUniform3fv(diffuseUniform, 1, value_ptr(this->material->mat.diffuse));
    
        GLint specularUniform = glGetUniformLocation(prog, "material.specular");
        glUniform3fv(specularUniform, 1, value_ptr(this->material->mat.specular));
    
        GLint ambientUniform = glGetUniformLocation(prog, "material.ambient");
        glUniform3fv(ambientUniform, 1, value_ptr(this->material->mat.ambient));
    
        GLint shininessUniform = glGetUniformLocation(prog, "material.shininess");
        glUniform1f(shininessUniform, this->material->mat.shininess*128);
    }
    
    GLint hasDiffuseTextureMapUniform = glGetUniformLocation(prog, "hasDiffuseTextureMap");
    glUniform1i(hasDiffuseTextureMapUniform, this->hasDiffuseTextureMap);
    
    if (prog == Program::FLAT) {
        GLint colourUniform = glGetUniformLocation(prog, "colour");
        glUniform4fv(colourUniform, 1, value_ptr(*this->colour));
    }
    
    mat4 model = translationMatrix*rotationMatrix*scaleMatrix;
    GLuint modelUniform = glGetUniformLocation(prog, "model");
    glUniformMatrix4fv(modelUniform, 1, false, value_ptr(model));
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexData.size());
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Primitive::update() {
    translationMatrix = glm::translate(mat4(), translation);
    rotationMatrix = toMat4(rotation);
    scaleMatrix = glm::scale(mat4(), scale*vec3(1));
}

void Primitive::setTranslation(vec3 translation) {
    this->translation = translation;
    update();
}

void Primitive::setRotation(vec3 eulerAngles) {
    this->rotation = quat(eulerAngles);
    update();
}

void Primitive::setScale(float scale) {
    this->scale = scale;
    update();
}

void Primitive::rotateAround(float angle, vec3 axis, vec3 point) {
    rotationMatrix = translate(mat4(), -translation);
    rotationMatrix = rotate(rotationMatrix, radians(angle), axis);
    rotationMatrix = translate(rotationMatrix, translation);
}
