//
//  Primitive.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/1/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Primitive_hpp
#define Primitive_hpp

#include <GL/glew.h>

#include "Texture.hpp"
#include "Material.hpp"
#include "Program.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BoundingBox.hpp"

using namespace glm;

class Primitive {
public:
    void render();
    void update();
    void setTranslation(vec3 translation);
    void setRotation(vec3 eulerAngles);
    void rotateAround(float angle, vec3 axis, vec3 point);
    void setScale(float scale);
    
    mat4 rotationMatrix = mat4();
    mat4 translationMatrix = mat4();
    mat4 scaleMatrix = mat4();
    
    bool SHADING_ENABLED = true;
    
    //Colours
    vec3 emissionMapColour = vec3(1,1,1);
    void setColour(vec4 colour);
protected:
    void init();
    
    GLuint VBO = 0;
    GLuint VAO = 0;
    GLuint EBO = 0;
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indicies;
    Texture* texture = NULL;
    
    Texture* diffuseMap = NULL;
    Texture* specularMap = NULL;
    Texture* emissionMap = NULL;
    
    Material* material = NULL;
    vec4* colour = NULL;
    
    //Transofrmation properties
    vec3 translation = vec3(0, 0, 0);
    quat rotation = quat(vec3(0 ,0 ,0));
    float scale = 1;
    
    bool hasTexture = false;
    bool hasTextureMaps = false;
    bool hasDiffuseMap = false;
    bool hasSpecularMap = false;
    bool hasEmissionMap = false;
    
    BoundingBox* box;
};

#endif /* Primitive_hpp */
