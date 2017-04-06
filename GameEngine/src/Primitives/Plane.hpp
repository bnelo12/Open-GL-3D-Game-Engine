//
//  Plane.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/3/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include "Primitive.hpp"

class Plane: public Primitive {
public:
    Plane(Material material);
private:
    void init();
};

#endif /* Plane_hpp */
