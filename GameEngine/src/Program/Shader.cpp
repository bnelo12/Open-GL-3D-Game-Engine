//
//  Shader.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/16/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//


#include "Shader.hpp"

#include <stdexcept>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

Shader::Shader(std::string filepath, GLenum shaderType) {
    std::ifstream f;
    f.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open()){
        throw std::runtime_error(std::string("Failed to open file: ") + filepath);
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    
    f.close();
    
    shaderid = glCreateShader(shaderType);
    
    const std::string tmp = buffer.str();
    const char* code = tmp.c_str();

    glShaderSource(shaderid, 1, (const GLchar**)&code, NULL);
    glCompileShader(shaderid);
    
    GLint status;
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE) {
        std::string msg("Compile failure in shader:\n");
        
        GLint infoLogLength;
        glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderid, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteShader(shaderid); shaderid = 0;
        throw std::runtime_error(msg);
    }
}

Shader::~Shader() {
    glDeleteShader(shaderid);
}
