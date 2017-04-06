//
//  DirectionalLight.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/4/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(vec3 intensities, vec3 direction): Light(intensities) {
    this->direction = direction;
}

