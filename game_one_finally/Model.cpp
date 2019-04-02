#include "pch.h"
#include "Model.h"




void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes.at(i).Draw(shader);
}

void Model::set_position(const char* path, glm::vec3 position)
{
	this->position_ = position;

}


void Model::load_data(Database database)
{

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	auto data = database.data.begin()._Ptr;
	for (auto i = data->vertices.begin();i< data->vertices.end();++i)
	{
		Vertex temp_ver;
		temp_ver.Position  = i._Ptr->Position + position_;
		temp_ver.Normal    = i._Ptr->Normal;
		temp_ver.TexCoords = i._Ptr->TexCoords;
		vertices.push_back(temp_ver);
	}

	indices = data->indices;
	textures = data->textures;
	this->meshes.emplace_back(vertices, indices, textures);
}


