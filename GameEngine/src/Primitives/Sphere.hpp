//
//  Sphere.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/1/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <glm/gtc/constants.hpp>
#include "Primitive.hpp"

class Sphere: public Primitive {
public:
    Sphere(Material material, int resolution);
    Sphere(vec4 colour, int resolution);
private:
    void init();
    int resolution;
    const float pi = glm::pi<float>();
};

#endif /* Sphere_hpp */
