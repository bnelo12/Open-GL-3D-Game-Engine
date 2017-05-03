//
//  Terrain.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/26/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include <GL/glew.h>
#include "Texture.hpp"
#include "Material.hpp"
#include "Program.hpp"
#include "Primitive.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Face {
    GLuint v1;
    GLuint v2;
    GLuint v3;
};

class Terrain : public Primitive {
public:
    Terrain(GLchar* heightmap, GLchar* textureFile);
private:
    GLchar* heightmap;
    void init();
    std::vector<Face> faces;
    void generateIndicies();
    int w;
    int h;
};

#endif /* Terrain_hpp */
