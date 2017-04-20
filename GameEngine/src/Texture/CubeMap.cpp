//
//  CubeMap.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/19/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "CubeMap.hpp"

using namespace std;

CubeMap::CubeMap(vector<GLchar*> textureFaces) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    SDL_Surface* textureImage;
    for (GLuint i = 0; i < textureFaces.size(); i++) {
        textureImage = IMG_Load(textureFaces[i]);
        int Mode = GL_RGB;
        if(textureImage->format->BytesPerPixel == 4) {
            Mode = GL_RGBA;
        }
        GLenum data_fmt;
        Uint8 test = SDL_MapRGB(textureImage->format, 0xAA,0xBB,0xCC)&0xFF;
        if      (test==0xAA) ((Mode == GL_RGB) ? data_fmt = GL_RGB : data_fmt = GL_RGBA);
        else if (test==0xCC) ((Mode == GL_RGB) ? data_fmt = GL_BGR : data_fmt = GL_BGRA);
        else {
            printf("Error: \"Loaded surface was neither RGB or BGR!\""); return;
        }
        glTexImage2D(
                     GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, Mode, textureImage->w, textureImage->h, 0, data_fmt, GL_UNSIGNED_BYTE, textureImage->pixels
                     );
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
