//
//  FPSCamera.cpp
//  GLTest
//
//  Created by Benjamin Elo on 3/2/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "FPSCamera.hpp"
#include <iostream>

FPSCamera::FPSCamera(vec3 offset, float xRot, float zRot) {
    this->offset = offset;
    this->xRot = glm::radians(xRot);
    this->zRot = glm::radians(zRot);
}

void FPSCamera::setWindow(SDL_Window *window) {
    this->window = window;
    SDL_GetWindowSize(window, &width, &height);
    aspectRatio = width/height;
    SDL_WarpMouseInWindow(window, width/2, height/2);
}

void FPSCamera::offestOrientation(float upOffset, float rightOffset) {
    zRot += rightOffset;
    xRot += upOffset;
    if (xRot > 87.f) xRot = 87.f;
    else if (xRot < -87.f) xRot = -87.f;
}

void FPSCamera::offsetPosition(vec3 offset) {
    this->offset += offset;
}

void FPSCamera::updateCamera() {
    const Uint8* ks = SDL_GetKeyboardState(NULL);
    if (!locked) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        this->offestOrientation(sensitivity*(mouseY-height/2), sensitivity*(mouseX-width/2));
        SDL_WarpMouseInWindow(window, width/2, height/2);

        if(ks[SDL_SCANCODE_W]) offsetPosition(-speed*forward());
        if(ks[SDL_SCANCODE_S]) offsetPosition(speed*forward());
        if(ks[SDL_SCANCODE_D]) offsetPosition(-speed*right());
        if(ks[SDL_SCANCODE_A]) offsetPosition(speed*right());
        
        projectionMat = perspective(radians(FOV), aspectRatio, nearPlane, farPlane);
        glm::mat4 finalVal = calculate();
        GLuint cameraUniform = 0;
        GLuint cameraPosUniform = 0;
        
        glUseProgram(Program::FLAT);
        cameraUniform = glGetUniformLocation(Program::FLAT, "camera");
        glUniformMatrix4fv(cameraUniform, 1, false, glm::value_ptr(finalVal));
        glUseProgram(0);
        
        glUseProgram(Program::PHONG);
        cameraUniform = glGetUniformLocation(Program::PHONG, "camera");
        glUniformMatrix4fv(cameraUniform, 1, false, glm::value_ptr(finalVal));
        cameraPosUniform = glGetUniformLocation(Program::PHONG, "cameraPos");
        glUniform3fv(cameraPosUniform, 1, glm::value_ptr(-this->offset));
        glUseProgram(0);
        
        glUseProgram(Program::LIGHTING_MAP);
        cameraUniform = glGetUniformLocation(Program::LIGHTING_MAP, "camera");
        glUniformMatrix4fv(cameraUniform, 1, false, glm::value_ptr(finalVal));
        cameraPosUniform = glGetUniformLocation(Program::LIGHTING_MAP, "cameraPos");
        glUniform3fv(cameraPosUniform, 1, glm::value_ptr(-this->offset));
        glUseProgram(0);
        
        glUseProgram(Program::SKY_BOX);
        cameraUniform = glGetUniformLocation(Program::SKY_BOX, "camera");
        glUniformMatrix4fv(cameraUniform, 1, false, glm::value_ptr(calculateSky()));
        glUseProgram(0);
    }
}

vec3 FPSCamera::forward() {
    glm::vec4 forward = glm::inverse(orientation) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

vec3 FPSCamera::right() {
    glm::vec4 right = glm::inverse(orientation) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

mat4 FPSCamera::calculate() {
    mat4 out;
    mat4 translation = translate(mat4(), offset);
    orientation = rotate(mat4(), radians(xRot), vec3(1,0,0));
    orientation = rotate(orientation, radians(zRot), vec3(0,1,0));
    out = projectionMat*orientation*translation;
    return out;
}

mat4 FPSCamera::calculateSky() {
    mat4 out;
    orientation = rotate(mat4(), radians(xRot), vec3(1,0,0));
    orientation = rotate(orientation, radians(zRot), vec3(0,1,0));
    out = projectionMat*orientation;
    return out;
}



void FPSCamera::lockCamera(bool lock) {
    SDL_ShowCursor(SDL_ENABLE);
    this->locked = lock;
}
