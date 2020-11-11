#pragma once
#include <string>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec2.hpp>
#include <vector>

enum textureType
{
	textureType_DIFFUSE = 1
};
struct material
{
	unsigned int GetTextureCount(textureType) { return 1; }
	/*std::string GetTexture(textureType, unsigned int,const std::string* str)
	{
		
	}*/
};
struct node
{
	
};
struct mesh_model
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCords;
	std::vector<unsigned int> indites;

};

struct scene
{
	int			 flags;
	node		 rootNode;
    mesh_model	     meshes;
	//Material** mMaterials;
};

class model_loader
{

public:
	scene read_file(const char*);
	model_loader();
	~model_loader();
};


