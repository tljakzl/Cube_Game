#pragma once
#include <unordered_map>
#include <mutex>
#include "Mesh.h"
#include "ChunkRender.h"

class RenderMaster
{
public:
    RenderMaster();
    ~RenderMaster() = default;

    void DrawMeshes(Shader* shader);
    void DrawChunks(Shader* shader);
    void AddMesh(Mesh*);
	void AddChunk(const std::string& key,ChunkRender&&);
	void UpdateChunk(const std::string& str, const std::vector<ChunkSection>& data);

private:
    std::vector<Mesh*> _dataMeshes;
    std::unordered_map<std::string, ChunkRender> _chunkMeshes;
    std::mutex _chunkMeshesMutex;
};

