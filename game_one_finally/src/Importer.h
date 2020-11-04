#pragma once
#include <string>
#include <glm/detail/type_vec3.hpp>


#define aiProcess_Triangulate 0x01
#define aiProcess_FlipUVs 0x02
#define AI_SCENE_FLAGS_INCOMPLETE 0x03



/*struct aiString
{
	
	char* C_Str()
	{
	}

};*/


enum  aiTextureType
{
	aiTextureType_DIFFUSE = 1,
	aiTextureType_SPECULAR = 2
};

struct aiMaterial
{
	//void GetTexture(aiTextureType, unsigned int, aiString*){}
	//unsigned int GetTextureCount(aiTextureType type){}
};
struct aiFace
{
	unsigned int  mNumIndices;
	unsigned int* mIndices;
};
struct aiMesh
{
	aiFace*		 mFaces;
	glm::vec2**  mTextureCoords;
	unsigned int mNumVertices;
	unsigned int mNumFaces;
	unsigned int mMaterialIndex;
	glm::vec3*   mVertices;
	glm::vec3*   mNormals;
};
struct aiNode
{
	unsigned int  mNumChildren;
	aiNode**	  mChildren;
	unsigned int  mNumMeshes;
	unsigned int* mMeshes;
};

struct aiScene
{
	int			 mFlags;
	aiNode*		 mRootNode;
	aiMesh**	 mMeshes;
	aiMaterial** mMaterials;
};


class Importer
{
public:
	std::string GetErrorString(){}
	aiScene& ReadFile(std::string, const int){}
	Importer();
	~Importer();
};



