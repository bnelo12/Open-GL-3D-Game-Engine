//
//  App.hpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/31/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include <string>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/color_space.hpp>

#include "Shader.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "FPSCamera.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "Plane.hpp"
#include "Tile.hpp"
#include "Model.hpp"

using namespace glm;

class App {
public:
    static void main();
private:
    static SDL_Window *mainWindow;
    static SDL_GLContext mainContext;
    static std::string programName;
    
    static bool init();
    static void setOpenGLAttributes();
    static void loadShaders();
    static void load();
    static void render();
    static void update();
    
    //World Objects
    static FPSCamera fpsCamera;
};

#endif /* App_hpp */
