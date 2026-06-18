#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


class Model 
{
    public:
		/*  模型数据  */
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture> textures_loaded;
        bool gammaCorrection;
        /*  函数   */
		// constructor, expects a filepath to a 3D model.
		Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
		{
			loadModel(path);
		}
        void Draw(Shader& shader);   
    private:
        
        /*  函数   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};








#endif
