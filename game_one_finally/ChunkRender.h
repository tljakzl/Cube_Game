#pragma once
#include "Mesh.h"
#include "Database.h"
#include "Chunk.h"


class ChunkRender
{
	Database* database_;
	Chunk* chunk_;

	void render(std::vector<blockInfo>);
public:

	std::vector<Mesh> chunk_mesh_;
	void update_mesh();
	void delete_block(glm::vec3);
	void draw(Shader shader);
	ChunkRender(Database*, Chunk*);
	~ChunkRender();
};

