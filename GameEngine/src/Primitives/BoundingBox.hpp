//
//  BoundingBox.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 5/8/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <GL/glew.h>

#include "Program.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class BoundingBox {
public:
    BoundingBox(std::vector<GLfloat> vertexData);
    void render();
    mat4 model = mat4();
private:
    void init(vec3 max, vec3 min);
    vec4* colour = NULL;
    vec3 maxMag(std::vector<GLfloat> vertexData);
    vec3 minMag(std::vector<GLfloat> vertexData);
    GLuint VBO = 0;
    GLuint VAO = 0;
    GLuint EBO = 0;
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indicies;
    float scale = 1;
};

#endif /* BoundingBox_hpp */
