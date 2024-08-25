#include "pch.h"
#include "Model.h"

void Model::Draw(Shader* shader)
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

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
    Texture* textures;

	auto data = database.data().begin();
	for (auto& i : database.GetVertices())
	{
		Vertex temp_ver;
		temp_ver.Position  = i.Position + position_;
		temp_ver.Normal    = i.Normal;
		temp_ver.TexCoords = i.TexCoords;
		vertices.push_back(temp_ver);
	}

	indices = data->GetIndices();
	textures = data->GetTexture();
	this->meshes.emplace_back(vertices, indices, textures);
}


void Model::load_data(Database database, std::vector<unsigned>* sides)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Texture* textures;

	auto data = database.data().begin();
/*	for (auto i = data->vertices.begin(); i < data->vertices.end(); ++i)
	{
		Vertex temp_ver;
		temp_ver.Position = i._Ptr->Position + position_;
		temp_ver.Normal = i._Ptr->Normal;
		temp_ver.TexCoords = i._Ptr->TexCoords;
		vertices.push_back(temp_ver);
	}*/

	auto ver = data->GetVertices();
	for (auto j = sides->begin(); j < sides->end(); ++j)
		for (auto i = 0; i < 6; ++i)
		{
			Vertex temp_ver;
			temp_ver.Position = ver.at(*j * 6 + i).Position + position_;
			temp_ver.Normal = ver.at(*j * 6 + i).Normal;
			temp_ver.TexCoords = ver.at(*j * 6 + i).TexCoords;
			vertices.push_back(temp_ver);
		}

	for(auto j = sides->begin(); j< sides->end();++j)
	for (auto i = 0; i < 6; ++i)
		indices.push_back(*j * 6 + i);
	textures = data->GetTexture();
	this->meshes.emplace_back(vertices, indices, textures);
}

void Model::clear_data()
{
	meshes.begin()->clear_data();
}



