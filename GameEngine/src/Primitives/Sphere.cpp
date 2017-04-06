//
//  Sphere.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 4/1/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Sphere.hpp"

Sphere::Sphere(Material material, int resolution) {
    this->material = new Material(material);
    this->resolution = resolution;
    init();
}

Sphere::Sphere(vec4 colour, int resolution) {
    this->SHADING_ENABLED = false;
    this->colour = new vec4(colour);
    this->resolution = resolution;
    init();
}

void Sphere::init() {
    float theta = 0;
    float phi = 0;
    
    float inc = pi/resolution;
    
    for (theta = 0; theta < 2*pi; theta += inc) {
        for (phi = 0; phi <= pi; phi += inc) {
            //Vertex Coords
            float x = cos(theta)*sin(phi);
            float y = sin(theta)*sin(phi);
            float z = cos(phi);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            vec3 normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
            //Vertex Coords
            x = cos(theta+inc)*sin(phi);
            y = sin(theta+inc)*sin(phi);
            z = cos(phi);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
            //Vertex Coords
            x = cos(theta+inc)*sin(phi+inc);
            y = sin(theta+inc)*sin(phi+inc);
            z = cos(phi+inc);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
            //Vertex Coords
            x = cos(theta)*sin(phi);
            y = sin(theta)*sin(phi);
            z = cos(phi);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
            //Vertex Coords
            x = cos(theta)*sin(phi+inc);
            y = sin(theta)*sin(phi+inc);
            z = cos(phi+inc);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
            //Vertex Coords
            x = cos(theta+inc)*sin(phi+inc);
            y = sin(theta+inc)*sin(phi+inc);
            z = cos(phi+inc);
            
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //UVCoords (Will impement later)
            vertexData.push_back(0);
            vertexData.push_back(0);
            
            //Normals
            normal = normalize(vec3(x, y, z));
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
            
        }
    }
    
    Primitive::init();
}
