#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <Mesh.h>
#include "vendor\stb_image\stb_image.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <unordered_map>

class Model
{
public:
	Model(string const& path)
	{
		GLCall(loadModel(path));
	}

	void Draw(Shader& shader);

private:
	// 模型数据
	vector<Mesh> meshes;
	// 模型数据所在目录
	string directory;
	// 记录已经加载过的纹理
	vector<std::shared_ptr<Texture>> textures_loaded;
	// 纹理文件到索引的哈希表
	unordered_map<string, unsigned int> texturesHashTable;


	// 从文件加载支持ASSIMP扩展的模型，并将生成的网格存储在网格矢量中。
	void loadModel(string const& path);

	// 以递归方式处理节点。 处理位于节点处的每个单独网格，并在其子节点（如果有）上重复此过程。
	void processNode(aiNode* node, const aiScene* scene);

	// 处理网格
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// 检查给定类型的所有材质纹理，如果尚未加载纹理，则加载纹理。
	// 所需信息作为Texture结构返回。
	vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName);
};
#endif


