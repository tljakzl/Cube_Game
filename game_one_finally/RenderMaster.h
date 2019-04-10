#pragma once
#include "Mesh.h"
#include "ChunkRender.h"

class RenderMaster
{
	std::vector<Mesh*> meshes_data_;
	std::vector<ChunkRender> chunk_meshes;
public:
	void add_mesh(Mesh*);
	void add_chunk(ChunkRender);
	void draw_meshes(Shader shader);
	void draw_chunks(Shader shader);
	RenderMaster();
	~RenderMaster();
};

