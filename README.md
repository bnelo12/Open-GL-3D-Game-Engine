# OpenGL 3D Game Engine
A 3D game engine created with OpenGL and regularly updated.

## Dependencies
SDL2

SDL2_Image

GLM

GLEW

## Update 2
### Diffuse, Specular, and Emission Lighting Maps
The game engine now has the ability to have different lighting maps including diffuse, specular, and emission maps. The cube primitive now has a constructor to take in a vector of Textures of different types and I have added a new fragment shader to handle the lighting maps. The images attached below demonstrate the new lighting maps in all their glory. The cubes have a shininess from the the specular map and a beautiful glow from the emssion map.

<img src="Examples/update2_animated.gif"/>
<img src="Examples/update2.png"/>

## Update 1

I am documententing my progress to create a modern OpenGL game engine. Before deciding to post my results on GitHub, I had created a simple Phong shader for the lighting model, and the ability to apply different shaders to different objects. I have three primitives in the primitive class: cube, sphere, and plane. I will attach a screen shot of my progress with each merge to the master branch.

<img src="Examples/update1.png"/>
