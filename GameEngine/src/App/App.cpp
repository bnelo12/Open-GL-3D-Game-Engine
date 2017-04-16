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
FPSCamera App::fpsCamera = FPSCamera(glm::vec3(0,-1,-5), 0, 0);
Cube* cube1;
Cube* cube2;
Light* light1;
Plane* plane1;
Model* sunflower;

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
    fpsCamera.setWindow(mainWindow);
    fpsCamera.setAspectRatio(1280.f/720.f);
    cube1 = new Cube(vector<Texture*>{new Texture("wooden-crate.jpg", MAP::DIFFUSE)});
    cube1->setTranslation(vec3(0,.5,0));
    cube1->setScale(.5);
    cube2 = new Cube(vector<Texture*>{new Texture("wooden-crate.jpg", MAP::DIFFUSE)});
    cube2->setTranslation(vec3(0,1.5,.1));
    cube2->setRotation(vec3(0,radians(-12.5f), 0));
    cube2->setScale(.5);
    light1 = new Light(vec3(8,9,0), vec3(1,1,1), vec3(1.f,1.f,1.f), vec3(.2,.2,.2));
    plane1 = new Plane(Material::GREEN_RUBBER);
    plane1->setTranslation(vec3(0,0,0));
    plane1->setScale(100);
    sunflower = new Model((GLchar*)"sunflower/sunflower.obj", vector<Texture*> {new Texture("sunflower/sunflower_diffuse.png", MAP::DIFFUSE)});
    sunflower->setScale(.1);
    sunflower->setTranslation(vec3(0,-.1,1.5));
    sunflower->setRotation(vec3(0, radians(30.f), 0));
}

void App::render() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    light1->render();
    cube1->render();
    cube2->render();
    plane1->render();
    sunflower->setTranslation(vec3(0,-.1,1.5));
    sunflower->setRotation(vec3(0, radians(30.f), 0));
    sunflower->render();
    sunflower->setTranslation(vec3(0,-.1,-1.5));
    sunflower->setRotation(vec3(0, radians(-30.f), 0));
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
