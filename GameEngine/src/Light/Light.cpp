//
//  Light.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/2/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Light.hpp"

Light::Light(vec3 diffuse, vec3 specular, vec3 ambient) {
    this->diffuse = diffuse;
    this->specular = specular;
    this->ambient = ambient;
    this->position = vec3(0,0,0);
}

Light::Light(vec3 position, vec3 diffuse, vec3 specular, vec3 ambient) {
    this->position = position;
    this->diffuse = diffuse;
    this->specular = specular;
    this->ambient = ambient;
    mesh = new Sphere(vec4(diffuse,1), 10);
    mesh->setTranslation(position);
    mesh->setScale(.1f);
    update();
}

void Light::render() {
    mesh->render();
}

void Light::rotateAround(float angle, vec3 axis, vec3 point) {
    mesh->rotateAround(angle, axis, point);
    this->rotation = this->mesh->rotationMatrix;
    update();
}

void Light::update() {
    vec3 position = vec3(translate(mat4(), this->position)*rotation*vec4(vec3(0),1));
    
    GLuint ambientUniform, diffuseUniform, specularUniform, posUniform;
    
    glUseProgram(Program::PHONG);
    ambientUniform = glGetUniformLocation(Program::PHONG, "light.ambient");
    glUniform3fv(ambientUniform, 1, value_ptr(this->ambient));
    diffuseUniform = glGetUniformLocation(Program::PHONG, "light.diffuse");
    glUniform3fv(diffuseUniform, 1, value_ptr(this->diffuse));
    specularUniform = glGetUniformLocation(Program::PHONG, "light.specular");
    glUniform3fv(specularUniform, 1, value_ptr(this->diffuse));
    posUniform = glGetUniformLocation(Program::PHONG, "light.position");
    glUniform3fv(posUniform, 1, value_ptr(position));
    glUseProgram(0);
    
    glUseProgram(Program::LIGHTING_MAP);
    ambientUniform = glGetUniformLocation(Program::LIGHTING_MAP, "light.ambient");
    glUniform3fv(ambientUniform, 1, value_ptr(this->ambient));
    diffuseUniform = glGetUniformLocation(Program::LIGHTING_MAP, "light.diffuse");
    glUniform3fv(diffuseUniform, 1, value_ptr(this->diffuse));
    specularUniform = glGetUniformLocation(Program::LIGHTING_MAP, "light.specular");
    glUniform3fv(specularUniform, 1, value_ptr(this->diffuse));
    posUniform = glGetUniformLocation(Program::LIGHTING_MAP, "light.position");
    glUniform3fv(posUniform, 1, value_ptr(position));
    glUseProgram(0);
}

void Light::setDiffuse(vec3 diffuse) {
    this->diffuse = diffuse;
    this->mesh->setColour(vec4(diffuse,1));
}

void Light::setAmbient(vec3 ambient) {
    this->ambient = ambient;
}

void Light::setSpecular(vec3 specular) {
    this->specular = specular;
}
