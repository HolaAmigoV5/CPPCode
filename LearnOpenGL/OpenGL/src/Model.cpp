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
/// ����ģ��
/// </summary>
/// <param name="path"></param>
void Model::loadModel(string const& path)
{
	Assimp::Importer importer;

	//ʹ��Assimp������ģ����Assimp��һ������scene�����ݽṹ��
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// ������
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// �����ļ�·����Ŀ¼·��
	directory = path.substr(0, path.find_last_of('/'));

	// �Եݹ鷽ʽ����ASSIMP�ĸ��ڵ�
	GLCall(processNode(scene->mRootNode, scene));
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// ����λ�ڵ�ǰ�ڵ��ÿ������
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// �ڵ��������������������������е�ʵ�ʶ���
		// ���������������ݣ��ڵ�ֻ��Ϊ������֯�ı��涫������ڵ�֮��Ĺ�ϵ����
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// �����Ǵ�����������������еĻ��������ǻ�ݹ鴦��ÿ���ӽڵ�
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// һ��Mesh������� Vertex(λ�� ������ ��������) 
	// ����������������� 
	// �������������
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<std::shared_ptr<Texture>> textures;

	// ������λ�� ���� ��������
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};

		// ��������һ��ռλ����������Ϊassimpʹ�����Լ��������࣬����ֱ��ת��Ϊglm��vec3�࣬�����������Ƚ����ݴ��ݸ����ռλ��glm :: vec3��
		glm::vec3 vector{};
		// λ��
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// ����
		if (mesh->mTextureCoords[0]) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		// ��������
		if (mesh->mTextureCoords[0]) // �����Ƿ�����������ꣿ
		{
			glm::vec2 vec{};
			// �������ɰ���8����ͬ���������ꡣ ��ˣ����Ǽ������ǲ���ʹ�ö�����Ծ��ж�����������ģ�ͣ�����������ǲ��õ�һ�����ϣ�0����
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
	//���ڱ���ÿ�������棨һ������һ�������ε����񣩲�������Ӧ�Ķ���������
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// ����������������������Ǵ洢������������
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// �ӹ�����
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// ���Ǽ�����ɫ���еĲ���������Լ���� ÿ������������Ӧ����Ϊ'texture_diffuseN'������N�Ǵ�1��MAX_SAMPLER_NUMBER�����кš�
	//ͬ�����������������������ܽ᣺
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. ��������ͼ
	vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. �߹���ͼ
	vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3.������ͼ
	std::vector<std::shared_ptr<Texture>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. �߶���ͼ
	std::vector<std::shared_ptr<Texture>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// ���ش���ȡ���������ݴ������������
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
			// δ���ع�
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
