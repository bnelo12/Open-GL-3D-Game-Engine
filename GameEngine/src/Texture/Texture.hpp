//
//  Texture.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/17/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>

#include <GL/glew.h>

class Texture {
public:
    Texture(const char* filename);
    GLuint textureid;
};

#endif /* Texture_hpp */
