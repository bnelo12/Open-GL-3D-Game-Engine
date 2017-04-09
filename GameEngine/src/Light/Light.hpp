//
//  Light.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/1/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sphere.hpp"
#include "Program.hpp"

using namespace glm;

class Light {
public:
    Light(vec3 position, vec3 diffuse, vec3 specular, vec3 ambient);
    void render();
    void rotateAround(float angle, vec3 axis, vec3 point);
    void setDiffuse(vec3 diffuse);
    void setSpecular(vec3 specular);
    void setAmbient(vec3 ambient);
protected:
    Light(vec3 diffuse, vec3 specular, vec3 ambient);
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
private:
    Sphere* mesh;
    vec3 position;
    mat4 rotation = mat4();

    void update();
};


#endif /* Light_hpp */
