//
//  Cube.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/27/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "Primitive.hpp"

using namespace glm;

class Cube: public Primitive {
public:
    Cube(char* textureFile, Material material);
    Cube(char* diffuseMap, char* specularMap);
    Cube(std::vector<Texture*> lightingMaps);
    Cube(Material material);
    Cube(vec4 colour);
private:
    void init();
};

#endif /* Cube_hpp */
