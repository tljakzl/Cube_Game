#pragma once
#include "Mesh.h"
#include "ChunkRender.h"
#include <unordered_map>

class RenderMaster
{
	std::vector<Mesh*> meshes_data_;
	std::unordered_map<std::string,ChunkRender> chunk_meshes;
public:
	void add_mesh(Mesh*);
	void add_chunk(std::string,ChunkRender);
	void draw_meshes(Shader shader);
	void draw_chunks(Shader shader);
	void update_chunk(std::string,std::vector<ChunkSection> data);
	RenderMaster();
	~RenderMaster();
};

