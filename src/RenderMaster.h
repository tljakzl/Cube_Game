#pragma once
#include "Mesh.h"
#include "ChunkRender.h"
#include <unordered_map>
#include <mutex>

class RenderMaster
{
	std::vector<Mesh*> meshes_data_;
	std::unordered_map<std::string, ChunkRender> chunk_meshes;
	std::mutex _chunkMeshesMutex;

public:
	void add_mesh(Mesh*);
	void add_chunk(std::string,ChunkRender&&);
	void draw_meshes(Shader* shader);
	void draw_chunks(Shader* shader);
	std::string GetStr() {return "Test, Jony";}
	void update_chunk(const std::string& str, const std::vector<ChunkSection>& data);
	RenderMaster();
	~RenderMaster();
};

