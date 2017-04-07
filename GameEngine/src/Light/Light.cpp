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
    mesh = new Sphere(vec4(1,1,1,1), 10);
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
    
    glUseProgram(Program::PHONG);
    
    GLint ambientUniform = glGetUniformLocation(Program::PHONG, "light.ambient");
    glUniform3fv(ambientUniform, 1, value_ptr(this->ambient));
    
    GLint diffuseUniform = glGetUniformLocation(Program::PHONG, "light.diffuse");
    glUniform3fv(diffuseUniform, 1, value_ptr(this->diffuse));
    
    GLint specularUniform = glGetUniformLocation(Program::PHONG, "light.specular");
    glUniform3fv(specularUniform, 1, value_ptr(this->diffuse));
    
    GLint posUniform = glGetUniformLocation(Program::PHONG, "light.position");
    glUniform3fv(posUniform, 1, value_ptr(position));
    
    glUseProgram(0);
}
