//
//  Program.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/17/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Program.hpp"

//PreDefined Programs
GLuint Program::FLAT;
GLuint Program::PHONG;
GLuint Program::LIGHTING_MAP;

Program::Program() {
}

Program::Program(std::vector<Shader*> shaders) {
    this->shaders = shaders;
    this->compile();
}

void Program::init() {
    Shader flatV = Shader("flatV.glsl", GL_VERTEX_SHADER);
    Shader flatF = Shader("flatF.glsl", GL_FRAGMENT_SHADER);
    Program::FLAT = (new Program({&flatV, &flatF}))->programid;
    
    Shader phongV = Shader("phongV.glsl", GL_VERTEX_SHADER);
    Shader phongF = Shader("phongF.glsl", GL_FRAGMENT_SHADER);
    Program::PHONG = (new Program({&phongF, &phongV}))->programid;
    
    Shader lightingMapV = Shader("lightingMapV.glsl", GL_VERTEX_SHADER);
    Shader lightingMapF = Shader("lightingMapF.glsl", GL_FRAGMENT_SHADER);
    Program::LIGHTING_MAP = (new Program({&lightingMapF, &lightingMapV}))->programid;
}

void Program::addShader(Shader *shader) {
    shaders.push_back(shader);
}

void Program::compile() {
    programid = glCreateProgram();
    for (int i = 0; i < shaders.size(); i++) {
        glAttachShader(programid, shaders[i]->shaderid);
    }
    
    glLinkProgram(programid);
    
    GLint isLinked = 0;
    glGetProgramiv(programid, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programid, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programid, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(programid);
        for (int i = 0; i < shaders.size(); i++) {
            glDetachShader(programid, shaders[i]->shaderid);
        }
        return;
    }
    
    for (int i = 0; i < shaders.size(); i++) {
        glDetachShader(programid, shaders[i]->shaderid);
    }
}

Program::~Program() {
    glDeleteProgram(programid);
}
