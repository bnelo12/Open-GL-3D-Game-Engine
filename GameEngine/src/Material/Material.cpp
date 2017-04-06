//
//  Material.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/4/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Material.hpp"

using namespace glm;

Material Material::EMERALD = Material(vec3(.0125, .1745, .0215), vec3(.07568, .61424, .07568), vec3(.633, .727811, .633), .6);
Material Material::JADE = Material(vec3(.135, .2225, .1575), vec3(.54, .89, .63), vec3(.316228, .316228, .316228), .1);
Material Material::OBSIDIAN = Material(vec3(.05375, .05, .06625), vec3(.18275, .17, .22525), vec3(.332741, .328634, .346435), .3);
Material Material::PEARL = Material(vec3(.25, .20725, 0.20725), vec3(1, 0.829, 0.829), vec3(0.296648, 0.296648, 0.296648), 0.088);
Material Material::RUBY = Material(vec3(0.1745, 0.01175, 0.01175), vec3(0.61424, 0.04136, 0.04136), vec3(0.727811, 0.626959, 0.626959), 0.6);
Material Material::TURQUOISE = Material(vec3(0.1, 0.18725, 0.1745), vec3(0.396, 0.74151, 0.69102), vec3(0.297254, 0.30829, 0.306678), 0.1);
Material Material::BRASS = Material(vec3(0.329412, 0.223529, 0.027451), vec3(0.780392, 0.568627, 0.113725), vec3(0.992157, 0.941176, 0.807843), 0.21794872);
Material Material::BRONZE = Material(vec3(0.2125, 0.1275, 0.054), vec3(0.714, 0.4284, 0.18144), vec3(0.393548, 0.271906, 0.166721), 0.2);
Material Material::CHROME = Material(vec3(0.25, 0.25, 0.25), vec3(0.4, 0.4, 0.4), vec3(0.774597, 0.774597, 0.774597), 0.6);
Material Material::COPPER = Material(vec3(0.19125, 0.0735, 0.0225), vec3(0.7038, 0.27048, 0.0828), vec3(0.256777, 0.137622, 0.086014), 0.1);
Material Material::GOLD = Material(vec3(0.24725, 0.1995, 0.0745), vec3(0.75164, 0.60648, 0.22648), vec3(0.628281, 0.555802, 0.366065), 0.4);
Material Material::SILVER = Material(vec3(0.19225, 0.19225, 0.19225), vec3(0.50754, 0.50754, 0.50754), vec3(0.508273, 0.508273, 0.508273), 0.4);
Material Material::BLACK_PLASTIC = Material(vec3(0.0, 0.0, 0.0), vec3(0.01, 0.01, 0.01), vec3(0.50, 0.50, 0.50), 0.25);
Material Material::CYAN_PLASTIC = Material(vec3(0.0, 0.1, 0.06), vec3(0.0, 0.50980392, 0.50980392), vec3(0.50196078, 0.50196078, 0.50196078), .25);
Material Material::GREEN_PLASTIC = Material(vec3(0.0, 0.0, 0.0), vec3(0.1, 0.35, 0.1), vec3(0.45, 0.55, 0.45), .25);
Material Material::RED_PLASTIC = Material(vec3(0.0, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.7, 0.6, 0.6), .25);
Material Material::WHITE_PLASTIC = Material(vec3(0.0, 0.0, 0.0), vec3(0.55, 0.55, 0.55), vec3(0.70, 0.70, 0.70), .25);
Material Material::YELLOW_PLASTIC = Material(vec3(0.0, 0.0, 0.0), vec3(0.5, 0.5, 0), vec3(0.60, 0.60, 0.50), .25);
Material Material::BLACK_RUBBER = Material(vec3(0.02, 0.02, 0.02), vec3(0.01, 0.01, 0.01), vec3(.4, .4, .4), .078125);
Material Material::CYAN_RUBBER = Material(vec3(0.0, 0.05, 0.05), vec3(0.4, 0.5, 0.5), vec3(0.04, 0.7, 0.7), .078125);
Material Material::GREEN_RUBBER = Material(vec3(0.0, 0.05, 0.0), vec3(0.4, 0.5, 0.4), vec3(0.04, 0.7, 0.04), .078125);
Material Material::RED_RUBBER = Material(vec3(0.05, 0.0, 0.0), vec3(0.5, 0.4, 0.4), vec3(0.7, 0.04, 0.04), .078125);
Material Material::WHITE_RUBBER = Material(vec3(0.05, 0.05, 0.05), vec3(0.5, 0.5, 0.5), vec3(0.7, 0.7, 0.7), .078125);
Material Material::YELLOW_RUBBER = Material(vec3(0.05, 0.05, 0), vec3(0.5, 0.5, 0.4), vec3(0.7, 0.7, 0.04), .078125);

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
    this->mat = material{ambient, diffuse, specular, shininess};
}
