//
//  FPSCamera.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/27/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef FPSCamera_hpp
#define FPSCamera_hpp

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.hpp"

using namespace glm;

class FPSCamera {
public:
    FPSCamera(vec3 offset, float xRot, float zRot);
    void init();
    
    void updateCamera();
    void offestOrientation(float up, float right);
    void offsetPosition(vec3 offset);
    void setWindow(SDL_Window* window);

    void setAspectRatio(float aspectRatio) {this->aspectRatio = aspectRatio;};
    void setFOV(float FOV) {this->FOV = FOV;};
    void setFarPlane(float farPlane) {this->farPlane = farPlane;};
    void setNearPlane(float nearPlane) {this->nearPlane = nearPlane;};
    
    void lockCamera(bool lock);
    
private:
    //player properties
    float speed = 0.2f;
    float sensitivity = .2;
    
    //camera properties
    float FOV = 50.0;
    float nearPlane = .1;
    float farPlane = 200;
    float zRot = 0;
    float xRot = 0;
    
    //window properties
    int width = 1280;
    int height = 720;
    float aspectRatio = 16.0/9.0;
    
    mat4 projectionMat = perspective(FOV, aspectRatio, nearPlane, farPlane);
    mat4 orientation;
    mat4 calculate();
    mat4 calculateSky();
    vec3 forward();
    vec3 right();
    vec3 offset;
    
    bool locked = false;
    
    SDL_Window* window;
    Program* gProgram;
};

#endif /* FPSCamera_hpp */
