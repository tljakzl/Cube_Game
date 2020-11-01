#pragma once
#include "Mesh.h"
#include "Database.h"
#include "Chunk.h"


class ChunkRender
{
	Database* database_;
	Chunk* chunk_;

	void render(const std::vector<blockInfo>&);
	void setup_mesh();
	int block_count = 0;
public:

	Mesh chunk_mesh_;
	void update_mesh(std::vector<ChunkSection> data);
	void delete_block(glm::vec3);
	void draw(Shader* shader);
	ChunkRender(Database*, Chunk*);
	~ChunkRender();
};

