//
//  Texture.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/17/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum class MAP {DIFFUSE, SPECULAR, EMISSION};

class Texture {
public:
    Texture(const char* filename, MAP type);
    GLuint textureID;
    MAP type;
private:
    GLuint textureUnit = 0;
};

#endif /* Texture_hpp */
