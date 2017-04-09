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

enum class MAP {DIFFUSE, SPECULAR, EMISSION};

class Texture {
public:
    Texture(const char* filename, MAP type);
    GLuint textureid;
    MAP type;
private:
    GLuint textureUnit = 0;
};

#endif /* Texture_hpp */
