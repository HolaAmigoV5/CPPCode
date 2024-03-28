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
	// ģ������
	vector<Mesh> meshes;
	// ģ����������Ŀ¼
	string directory;
	// ��¼�Ѿ����ع�������
	vector<std::shared_ptr<Texture>> textures_loaded;
	// �����ļ��������Ĺ�ϣ��
	unordered_map<string, unsigned int> texturesHashTable;


	// ���ļ�����֧��ASSIMP��չ��ģ�ͣ��������ɵ�����洢������ʸ���С�
	void loadModel(string const& path);

	// �Եݹ鷽ʽ����ڵ㡣 ����λ�ڽڵ㴦��ÿ���������񣬲������ӽڵ㣨����У����ظ��˹��̡�
	void processNode(aiNode* node, const aiScene* scene);

	// ��������
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// ���������͵����в������������δ�����������������
	// ������Ϣ��ΪTexture�ṹ���ء�
	vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName);
};
#endif


