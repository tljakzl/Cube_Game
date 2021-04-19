#include "pch.h"
#include "RenderMaster.h"


RenderMaster::RenderMaster()
    :_dataMeshes()
    ,_chunkMeshes()
    ,_chunkMeshesMutex()
{
}

void RenderMaster::AddMesh(Mesh* mesh_ptr)
{
	_dataMeshes.push_back(mesh_ptr);
}
void RenderMaster::DrawMeshes(Shader* shader)
{
	for (auto& cur_mesh : _dataMeshes)
	{
		cur_mesh->Draw(shader);
	}
}
void RenderMaster::DrawChunks(Shader* shader)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock)
    {
        for (auto& cur_chunk : _chunkMeshes) {
            cur_chunk.second.draw(shader);
        }
    }
}
void RenderMaster::AddChunk(const std::string& key, ChunkRender&& chunk)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock) {
        _chunkMeshes.emplace(key, chunk);
    }
}

void RenderMaster::UpdateChunk(const std::string& key, const std::vector<ChunkSection>& data)
{
    std::unique_lock<std::mutex> lock{_chunkMeshesMutex};
    if(lock) {
        auto&& iter = _chunkMeshes.find(key);
        if (iter != _chunkMeshes.end()) {
            iter->second.update_mesh(data);
        }
    }
}




