//
//  Material.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/4/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

struct material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

class Material {
public:
    Material(vec3 ambient,
             vec3 diffuse,
             vec3 specular,
             float shininess);
    
    material mat;
    
    static Material EMERALD;
    static Material JADE;
    static Material OBSIDIAN;
    static Material PEARL;
    static Material RUBY;
    static Material TURQUOISE;
    static Material BRASS;
    static Material BRONZE;
    static Material CHROME;
    static Material COPPER;
    static Material GOLD;
    static Material SILVER;
    static Material BLACK_PLASTIC;
    static Material CYAN_PLASTIC;
    static Material GREEN_PLASTIC;
    static Material RED_PLASTIC;
    static Material WHITE_PLASTIC;
    static Material YELLOW_PLASTIC;
    static Material BLACK_RUBBER;
    static Material CYAN_RUBBER;
    static Material GREEN_RUBBER;
    static Material RED_RUBBER;
    static Material WHITE_RUBBER;
    static Material YELLOW_RUBBER;
};

#endif /* Material_hpp */
