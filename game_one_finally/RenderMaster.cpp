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
void RenderMaster::draw_meshes(Shader shader)
{
	for (auto cur_mesh : meshes_data_)
	{
		cur_mesh->Draw(shader);
	}
}
void RenderMaster::draw_chunks(Shader shader)
{
	for (auto cur_chunk : chunk_meshes)
	{
		cur_chunk.draw(shader);
	}
}
void RenderMaster::add_chunk(ChunkRender chunk)
{
	this->chunk_meshes.push_back(chunk);
}



