//
//  Light.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/2/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Light.hpp"

float Light::ambient = .1;

Light::Light(vec3 intensities) {
    this->intensities = intensities;
    this->position = vec3(0,0,0);
}

Light::Light(vec3 position, vec3 intensities) {
    this->position = position;
    this->intensities = intensities;
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

void Light::setAmbient(float ambient) {
    Light::ambient = ambient;
}

void Light::update() {
    vec3 position = vec3(translate(mat4(), this->position)*rotation*vec4(vec3(0),1));
    glUseProgram(Program::PHONG);
    GLint ambientUniform = glGetUniformLocation(Program::PHONG, "ambientStrength");
    glUniform1f(ambientUniform, Light::ambient);
    
    GLint colorUniform = glGetUniformLocation(Program::PHONG, "lightColor");
    glUniform3fv(colorUniform, 1, value_ptr(this->intensities));
    
    GLint posUniform = glGetUniformLocation(Program::PHONG, "lightPosition");
    glUniform3fv(posUniform, 1, value_ptr(position));
    
    glUseProgram(0);
}
