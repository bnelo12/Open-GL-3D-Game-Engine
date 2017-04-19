//
//  Model.hpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/12/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

#include "Program.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

using namespace std;

class Model
{
public:
    Model(GLchar* path, vector<Texture*> textures);
    void render();
    void update();
    void setTranslation(vec3 translation);
    void setRotation(vec3 eulerAngles);
    void rotateAround(float angle, vec3 axis, vec3 point);
    void setScale(float scale);
private:
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    
    vector<Texture*> textures;
};

#endif /* Model_hpp */
