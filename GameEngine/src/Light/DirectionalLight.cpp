//
//  DirectionalLight.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/4/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(vec3 direction, vec3 diffuse, vec3 specular, vec3 ambient): Light(diffuse, specular, ambient) {
    this->direction = direction;
}

