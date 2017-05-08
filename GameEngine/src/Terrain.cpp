//
//  Terrain.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/26/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Terrain.hpp"

Uint32 getPixelIntensity(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[(y*surface->w) + x]&0x000000FF;
}

Terrain::Terrain(GLchar* heightmap, GLchar* textureFile) {
    this->heightmap = heightmap;
    this->hasTextureMaps  = true;
    this->diffuseMap = new Texture(textureFile, MAP::DIFFUSE);
    init();
}

void Terrain::generateIndicies() {
    glGenBuffers(1, &EBO);
    for (GLuint y = 0; y < h-1; y++) {
        for (GLuint x = 0; x < w-1; x++) {
            faces.push_back(Face{x+y*w, (x+y*w)+1, x+(y+1)*w});
            faces.push_back(Face{(x+(y+1)*w)+1, x+(y+1)*w, (x+y*w)+1});
            indicies.insert(indicies.end(), {
                x+y*w, (x+y*w)+1, x+(y+1)*w,
                (x+y*w)+1, x+(y+1)*w, (x+(y+1)*w)+1
            });
        }
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::init() {
    SDL_Surface* textureImage;
    textureImage = IMG_Load(heightmap);
    this->w = textureImage->w;
    this->h = textureImage->h;
    
    generateIndicies();
    
    std::vector<vec3> vpositions;
    std::vector<vec3> vnormals;
    std::vector<vec2> vUVs;
    
    for (GLuint y = 0; y < textureImage->h; y++) {
        for(GLuint x = 0; x < textureImage->w; x++) {
            GLfloat h = getPixelIntensity(textureImage, x, y)/5.f;
            vpositions.push_back(vec3((GLfloat)x-w/2, h, (GLfloat)y-w/2));
            vnormals.push_back(vec3(0));
            vUVs.push_back(vec2((GLfloat)(x*.1),(GLfloat)(y*.1)));
        }
    }
    
    for (Face f : faces) {
        vec3 e1 = vpositions[f.v2] - vpositions[f.v1];
        vec3 e2 = vpositions[f.v3] - vpositions[f.v1];
        vec3 no = cross(e2, e1);
        vnormals[f.v1] += no;
        vnormals[f.v2] += no;
        vnormals[f.v3] += no;
    }
    
    for (int i = 0; i < vpositions.size(); i++) {
        vec3 v = vpositions[i];
        vec3 n = vnormals[i];
        vec2 UV = vUVs[i];
        vertexData.insert(vertexData.end(), {v.x, v.y, v.z, UV.x, UV.y, n.x, n.y, n.z});
    }
    
    delete textureImage;
    
    Primitive::init();
}
