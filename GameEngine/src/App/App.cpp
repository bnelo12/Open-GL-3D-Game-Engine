//
//  App.cpp
//  OpenGL2
//
//  Created by Benjamin Elo on 3/31/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "App.hpp"

using namespace std;

std::string App::programName = "OpenGL";
SDL_Window* App::mainWindow;
SDL_GLContext App::mainContext;

//World Objects
FPSCamera App::fpsCamera = FPSCamera(glm::vec3(-5,-2,-5), 0, 0);
Light* light1;
Tile* grassField;
Cube* cube1;
Cube* cube2;
Model* sunflower;
Model* barn;
CubeMap* map;
SkyBox* env;
vector<Model> sunflowers;
Terrain* terrain;

void App::setOpenGLAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void App::loadShaders() {
    Program::init();
}

void App::load() {
    terrain = new Terrain((GLchar*) "heightmap.jpg", (GLchar*)"grass_diffuse.jpg");
    map = new CubeMap(vector<GLchar*>{
        (GLchar*)"miramar/miramar_ft.tga",
        (GLchar*)"miramar/miramar_bk.tga",
        (GLchar*)"miramar/miramar_up.tga",
        (GLchar*)"miramar/miramar_dn.tga",
        (GLchar*)"miramar/miramar_rt.tga",
        (GLchar*)"miramar/miramar_lf.tga"});
    env = new SkyBox(map);
    
    // Set Camera
    fpsCamera.setWindow(mainWindow);
    fpsCamera.setAspectRatio(1280.f/720.f);
    
    // Set Lights
    light1 = new Light(vec3(100,500,500), vec3(1,1,1), vec3(1.f,1.f,1.f), vec3(.2,.2,.2));
    
    // Load Primitives
    grassField = new Tile(vector<Texture*> {new Texture("grass_diffuse.jpg", MAP::DIFFUSE)}, 20);
    
    //Load Models
    sunflower = new Model( (GLchar*)"sunflower/sunflower.obj",
                           vector<Texture*> {
                               new Texture("sunflower/sunflower_diffuse.png", MAP::DIFFUSE)
                           });
    barn = new Model( (GLchar*)"medieval_barn/medieval_barn.obj",
                          vector<Texture*> {
                              new Texture("medieval_barn/medieval_barn.png", MAP::DIFFUSE)
                          });
    
    // Set Transformations
    barn->setRotation(vec3(0, radians(-60.f), 0));
    barn->setTranslation(vec3(-25,10.9,-30));
    barn->setScale(2);
    sunflower->setScale(.1);
    sunflower->setTranslation(vec3(-24,10.2,-28));
    sunflower->setRotation(vec3(0, radians(-40.f), 0));
    cube1 = new Cube(vector<Texture*>{new Texture("wooden-crate.jpg", MAP::DIFFUSE)});
    cube1->setTranslation(vec3(2,.5,-1.2));
    cube1->setScale(.5);
    cube2 = new Cube(vector<Texture*>{new Texture("wooden-crate.jpg", MAP::DIFFUSE)});
    cube2->setTranslation(vec3(2,1.5,-1.2));
    cube2->setRotation(vec3(0,radians(-12.5f), 0));
    cube2->setScale(.5);
}

void App::render() {
    glClearColor(0, .75, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    env->render();
    light1->render();
    cube1->render();
    cube2->render();
    barn->render();
    terrain->render();
    sunflower->render();
    SDL_GL_SwapWindow(mainWindow);
}

void App::update() {
    fpsCamera.updateCamera();
}

bool App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to init SDL\n";
        return false;
    }
    
    setOpenGLAttributes();
    
    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    
    if (!mainWindow) {
        std::cout << "Unable to create window\n";
        return false;
    }
    
    mainContext = SDL_GL_CreateContext(mainWindow);
    SDL_GL_SetSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    SDL_ShowCursor(SDL_DISABLE);
    
    loadShaders();
    load();
    
    return true;
}

void App::main() {
    init();
    
    bool loop = true;
    
    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) loop = false;
            
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_l:
                        fpsCamera.lockCamera(true);
                    default:
                        break;
                }
            }
        }
        render();
        update();
    }
    
}
