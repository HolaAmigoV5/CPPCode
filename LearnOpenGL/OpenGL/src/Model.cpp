#include "Model.h"
#include "Texture.h"

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
		
	}
}

/// <summary>
/// 导入模型
/// </summary>
/// <param name="path"></param>
void Model::loadModel(string const& path)
{
	Assimp::Importer importer;

	//使用Assimp来加载模型至Assimp的一个叫做scene的数据结构中
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// 检查错误
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// 检索文件路径的目录路径
	directory = path.substr(0, path.find_last_of('/'));

	// 以递归方式处理ASSIMP的根节点
	GLCall(processNode(scene->mRootNode, scene));
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// 处理位于当前节点的每个网格
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// 节点对象仅包含索引用来索引场景中的实际对象。
		// 场景包含所有数据，节点只是为了有组织的保存东西（如节点之间的关系）。
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// 在我们处理完所有网格（如果有的话）后，我们会递归处理每个子节点
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// 一个Mesh对象包括 Vertex(位置 法向量 纹理坐标) 
	// 绘制所需的索引数组 
	// 绘制所需的纹理
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<std::shared_ptr<Texture>> textures;

	// 处理顶点位置 法线 纹理坐标
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};

		// 我们声明一个占位符向量，因为assimp使用它自己的向量类，它不直接转换为glm的vec3类，所以我们首先将数据传递给这个占位符glm :: vec3。
		glm::vec3 vector{};
		// 位置
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// 法线
		if (mesh->mTextureCoords[0]) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		// 纹理坐标
		if (mesh->mTextureCoords[0]) // 网格是否包含纹理坐标？
		{
			glm::vec2 vec{};
			// 顶点最多可包含8个不同的纹理坐标。 因此，我们假设我们不会使用顶点可以具有多个纹理坐标的模型，因此我们总是采用第一个集合（0）。
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;

			//// tangent
			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;
			//// bitangent
			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	//现在遍历每个网格面（一个面是一个三角形的网格）并检索相应的顶点索引。
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// 检索面的所有索引并将它们存储在索引向量中
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// 加工材料
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// 我们假设着色器中的采样器名称约定。 每个漫反射纹理应命名为'texture_diffuseN'，其中N是从1到MAX_SAMPLER_NUMBER的序列号。
	//同样适用于其他纹理，如下列总结：
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. 漫反射贴图
	vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. 高光贴图
	vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3.法线贴图
	std::vector<std::shared_ptr<Texture>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. 高度贴图
	std::vector<std::shared_ptr<Texture>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// 返回从提取的网格数据创建的网格对象
	return Mesh(vertices, indices, textures);
}

vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName)
{
	vector<std::shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString textureFilePosition;
		mat->GetTexture(type, i, &textureFilePosition);
		string str(textureFilePosition.C_Str());
		auto it = texturesHashTable.find(str);
		if (it == texturesHashTable.end()) {
			// 未加载过
			texturesHashTable[str] = static_cast<unsigned int>(textures_loaded.size());
			auto texture_ptr = std::make_shared<Texture>(typeName, directory + "/" + str, false);
			textures_loaded.push_back(texture_ptr);
			textures.push_back(texture_ptr);
		}
		else
			textures.push_back(textures_loaded[it->second]);
	}
	return textures;
}
