//
//  DirectionalLight.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/4/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include "Light.hpp"

class DirectionalLight: public Light {
public:
    DirectionalLight(vec3 direction, vec3 diffuse, vec3 specular, vec3 ambient);
private:
    vec3 direction;
};

#endif /* DirectionalLight_hpp */
