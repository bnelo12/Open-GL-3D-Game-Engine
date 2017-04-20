//
//  SkyBox.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/19/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp

#include "CubeMap.hpp"
#include "Program.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class SkyBox {
public:
    SkyBox(CubeMap* map);
    void render();
private:
    GLuint VBO = 0;
    GLuint VAO = 0;
    
    CubeMap* map;
    void init();
};

#endif /* SkyBox_hpp */
