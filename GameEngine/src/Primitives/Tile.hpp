//
//  Tile.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/16/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "Primitive.hpp"

class Tile : public Primitive {
public:
    Tile(std::vector<Texture*> lightingMaps, int radius);
private:
    void init();
    int radius;
};

#endif /* Tile_hpp */
