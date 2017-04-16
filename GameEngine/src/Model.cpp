//
//  Model.cpp
//  OpenGLGameEngine
//
//  Created by Benjamin Elo on 4/12/17.
//  Copyright © 2017 Elo Software. All rights reserved.
//

#include "Model.hpp"

using namespace std;

Model::Model(GLchar* path, vector<Texture*> textures) {
    this->textures = textures;
    this->loadModel(path);
}

void Model::render() {
    for (Mesh mesh : this->meshes) {
        mesh.render();
    }
}

void Model::loadModel(string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
        }
        else
            vertex.uv = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return Mesh(vertices, indices, this->textures);
}

void Model::setScale(float scale) {
    for (Mesh &mesh : this->meshes) {
        mesh.setScale(scale);
    }
}

void Model::setTranslation(vec3 translation) {
    for (Mesh &mesh : this->meshes) {
        mesh.setTranslation(translation);
    }
}

void Model::setRotation(vec3 eulerAngles) {
    for (Mesh &mesh : this->meshes) {
        mesh.setRotation(eulerAngles);
    }
}
