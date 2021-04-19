#include "pch.h"
#include "RenderMaster.h"


RenderMaster::RenderMaster()
    :meshes_data_()
    ,chunk_meshes()
    ,_chunkMeshesMutex()
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
	for (auto& cur_mesh : meshes_data_)
	{
		cur_mesh->Draw(shader);
	}
}
void RenderMaster::draw_chunks(Shader* shader)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock)
    {
        for (auto& cur_chunk : chunk_meshes) {
            cur_chunk.second.draw(shader);
        }
    }
}
void RenderMaster::add_chunk(std::string key, ChunkRender&& chunk)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock) {
        chunk_meshes.emplace(key, chunk);
    }
}

void RenderMaster::update_chunk(const std::string& key, const std::vector<ChunkSection>& data)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock) {
        auto&& iter = chunk_meshes.find(key);
        if (iter != chunk_meshes.end()) {
            iter->second.update_mesh(data);
        }
    }
}




