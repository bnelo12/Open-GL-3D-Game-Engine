# OpenGL 3D Game Engine
A 3D game engine created with OpenGL and regularly updated.

## Dependencies
SDL2

SDL2_Image

GLM

GLEW

## Update 3
### Model Loading
Model loading is now a feature. I am using th Assimp library so that models of different types can be loaded, including .3ds, .obj, and .max. This converts the model to an intermediate XML like format, which is then parsed by my own code so that it can work in my game engine. The main benefit to using Assimp is to support a large range of different object files. The constructor for the model class takes in a 3d model file and a vector of different texture types. Right now the model loading can onlytake in models composed of one mesh, and that contain one of each type of texture. It works in the same way that the cube class below works, so for instance if I wanted to load in the sunflower object file I would use the constructor as such,

```cpp
sunflower = new Model(
    (GLchar*)"sunflower/sunflower.obj", 
    vector<Texture*> {
        new Texture("sunflower/sunflower_diffuse.png", MAP::DIFFUSE)
    }
);
```
With the results below,
<img src="Examples/update3.png"/>
The next improvements I will make with this is instancing, such that I can display multiple copies of the same object more efficiently.

## Update 2
### Diffuse, Specular, and Emission Lighting Maps
The game engine now has the ability to have different lighting maps including diffuse, specular, and emission maps. The cube primitive now has a constructor to take in a vector of Textures of different types and I have added a new fragment shader to handle the lighting maps. The images attached below demonstrate the new lighting maps in all their glory. The cubes have a shininess from the the specular map and a beautiful glow from the emssion map.

<img src="Examples/update2_animated.gif"/>
<img src="Examples/update2.png"/>

## Update 1

I am documententing my progress to create a modern OpenGL game engine. Before deciding to post my results on GitHub, I had created a simple Phong shader for the lighting model, and the ability to apply different shaders to different objects. I have three primitives in the primitive class: cube, sphere, and plane. I will attach a screen shot of my progress with each merge to the master branch.

<img src="Examples/update1.png"/>
