#include "pch.h"
#include "RenderMaster.h"


RenderMaster::RenderMaster()
{
}


RenderMaster::~RenderMaster()
{
}

void RenderMaster::add_mesh(Mesh* mesh_ptr)
{
	this->meshes_data_.push_back(mesh_ptr);
}
void RenderMaster::draw_meshes(Shader* shader)
{
	for (auto cur_mesh : meshes_data_)
	{
		cur_mesh->Draw(shader);
	}
}
void RenderMaster::draw_chunks(Shader* shader)
{
	for (auto cur_chunk : chunk_meshes)
	{
		cur_chunk.second.draw(shader);
	}
}
void RenderMaster::add_chunk(std::string key,ChunkRender chunk)
{
	this->chunk_meshes.emplace(key,chunk);
}

void RenderMaster::update_chunk(std::string key,std::vector<ChunkSection> data)
{
	this->chunk_meshes.at(key).update_mesh(data);
}




