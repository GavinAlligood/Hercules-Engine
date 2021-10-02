#pragma once

#include "../GL/Shader/Shader.h"
#include "../GL/Texture/Texture.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//TODO: Change all these to uppercase

namespace Hercules {
    class Model
    {
    public:
        // model data
        //std::vector<MeshTexture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        Model(std::string path)
        {
            loadModel(path);
        }

        void Draw(Texture& texture, glm::vec3& pos, glm::vec3& scale,
            glm::vec3& rotation, Shader* shader);

        unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
    private:
        
        

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
       /* std::vector<MeshTexture> loadMaterialTextures(aiMaterial * mat, aiTextureType type,
            std::string typeName);*/

        
    };
}