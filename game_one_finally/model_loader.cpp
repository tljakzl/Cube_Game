#include "pch.h"
#include "model_loader.h"
#include <sstream>
#include <fstream>
#include <vector>



model_loader::model_loader()
{
}


model_loader::~model_loader()
{
}


scene model_loader::read_file(const char* path)
{

	char v[]  = "v";
	char vt[] = "vt";
	char vn[] = "vn";
	char f[]  = "f";
	
	std::ifstream file;
	
	glm::vec3 temp_ver;
	std::vector<glm::vec3> temp_vector_ver;

	glm::vec3 temp_normal;
	std::vector<glm::vec3> temp_vector_normals;

	glm::vec2 temp_texCord;
	std::vector<glm::vec2> temp_vector_texCord;


	mesh out_mesh;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);
		std::string currentWord;

		while (!file.eof())
		{
			file >> currentWord;

			if (currentWord == v)
			{
				file >> temp_ver.x;
				file >> temp_ver.y;
				file >> temp_ver.z;
				temp_vector_ver.push_back(temp_ver);
			}
			if (currentWord == vt)
			{
				file >> temp_texCord.x;
				file >> temp_texCord.y;
				temp_vector_texCord.push_back(temp_texCord);
			}
			if (currentWord == vn)
			{
				file >> temp_normal.x;
				file >> temp_normal.y;
				file >> temp_normal.z;
				temp_vector_normals.push_back(temp_normal);
			}

			if (currentWord == f)
			{
				int i;
				char trash;
				for (auto j = 0; j < 3; ++j)
				{
					file >> i;
					out_mesh.vertices.push_back(temp_vector_ver.at(i-1));
					file >> trash;

					file >> i;
					out_mesh.textureCords.push_back(temp_vector_texCord.at(i-1));
					file >> trash;

					file >> i;
					out_mesh.normals.push_back(temp_vector_normals.at(i-1));
				}


			}

		}
		
		
		scene out_scene;
		out_scene.meshes = out_mesh;
		return out_scene;

	}
	catch (...)
	{
		throw;
	}
	
	
	

	
	

}
