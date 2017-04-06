//
//  Texture.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/17/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.hpp"

Texture::Texture(const char* filename) {
    SDL_Surface* textureImage;
    textureImage = IMG_Load(filename);
    glGenTextures(1, &textureid);
    
    glBindTexture(GL_TEXTURE_2D, textureid);
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
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, textureImage->w, textureImage->h, 0, data_fmt, GL_UNSIGNED_BYTE, textureImage->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
