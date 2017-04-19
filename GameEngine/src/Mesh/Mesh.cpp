//
//  Mesh.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/11/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures) {
    this->vertices = vertices;
    this->indices = indices;
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
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
                 &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, uv));
    
    glBindVertexArray(0);
}

void Mesh::render() {
    GLuint prog = 0;
    
    if (hasTextureMaps) {
        prog = Program::LIGHTING_MAP;
        glUseProgram(prog);
        
        if(diffuseMap) {
            this->hasDiffuseMap = true;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap->textureid);
            GLint mapUniform = glGetUniformLocation(prog, "diffuse_map");
            glUniform1i(mapUniform, 0);
        }
        if(specularMap) {
            this->hasSpecularMap = true;
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap->textureid);
            GLint mapUniform = glGetUniformLocation(prog, "specular_map");
            glUniform1i(mapUniform, 1);
        }
        if(emissionMap) {
            this->hasEmissionMap = true;
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, emissionMap->textureid);
            GLint mapUniform = glGetUniformLocation(prog, "emission_map");
            glUniform1i(mapUniform, 2);
        }
        glUniform1i(glGetUniformLocation(prog, "hasDiffuseMap"), this->hasDiffuseMap);
        glUniform1i(glGetUniformLocation(prog, "hasSpecularMap"), this->hasSpecularMap);
        glUniform1i(glGetUniformLocation(prog, "hasEmissionMap"), this->hasEmissionMap);
        glUniform3fv(glGetUniformLocation(prog, "emissionMapColour"), 1, value_ptr(this->emissionMapColour));
    }
    else if (!hasTextureMaps) {
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
        
        GLint hasTextureUniform = glGetUniformLocation(prog, "hasDiffuseTextureMap");
        glUniform1i(hasTextureUniform, this->hasTexture);
        
        if (prog == Program::FLAT) {
            GLint colourUniform = glGetUniformLocation(prog, "colour");
            glUniform4fv(colourUniform, 1, value_ptr(*this->colour));
        }
    }
    
    mat4 model = translationMatrix*rotationMatrix*scaleMatrix;
    GLuint modelUniform = glGetUniformLocation(prog, "model");
    glUniformMatrix4fv(modelUniform, 1, false, value_ptr(model));
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glBindVertexArray(0);
    glUseProgram(0);

}

void Mesh::update() {
    translationMatrix = glm::translate(mat4(), translation);
    rotationMatrix = toMat4(rotation);
    scaleMatrix = glm::scale(mat4(), scale*vec3(1));
}

void Mesh::setTranslation(vec3 translation) {
    this->translation = translation;
    update();
}

void Mesh::setRotation(vec3 eulerAngles) {
    this->rotation = quat(eulerAngles);
    update();
}

void Mesh::setScale(float scale) {
    this->scale = scale;
    update();
}


void Mesh::rotateAround(float angle, vec3 axis, vec3 point) {
    rotationMatrix = translate(mat4(), -translation);
    rotationMatrix = rotate(rotationMatrix, radians(angle), axis);
    rotationMatrix = translate(rotationMatrix, translation);
}
