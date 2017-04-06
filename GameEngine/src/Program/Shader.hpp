//
//  Shader.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/16/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(std::string filepath, GLenum shaderType);
    ~Shader();
    GLuint shaderid;
};

#endif /* Shader_hpp */
