//
//  Program.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/17/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <GL/glew.h>
#include <vector>
#include "Shader.hpp"

class Program {
public:
    Program();
    Program(std::vector<Shader*> shaders);
    void compile();
    void addShader(Shader* shader);
    GLuint programid = 0;
    ~Program();
    
    //Initialize predefined shaders
    static void init();
    
    //Shader Programs
    static GLuint FLAT;
    static GLuint PHONG;
    static GLuint LIGHTING_MAP;
    static GLuint SKY_BOX;
    
private:
    std::vector<Shader*> shaders;
};

#endif /* Program_hpp */
