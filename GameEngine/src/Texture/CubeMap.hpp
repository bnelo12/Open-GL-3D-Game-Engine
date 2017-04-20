//
//  CubeMap.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/19/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef CubeMap_hpp
#define CubeMap_hpp

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

using namespace std;

class CubeMap {
public:
    CubeMap(vector<GLchar*> textureFaces);
    GLuint textureID;
};

#endif /* CubeMap_hpp */
