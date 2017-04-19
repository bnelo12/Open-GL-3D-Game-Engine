//
//  Mesh.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/11/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>

#include "Texture.hpp"
#include "Material.hpp"
#include "Program.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace glm;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures);
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

private:
    GLuint VBO, VAO, EBO;
    void init();
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

};

#endif /* Mesh_hpp */
