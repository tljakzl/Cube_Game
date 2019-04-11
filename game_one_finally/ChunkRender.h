#pragma once
#include "Mesh.h"
#include "Database.h"
#include "Chunk.h"


class ChunkRender
{
	Database* database_;
	Chunk* chunk_;

	void render(std::unordered_map<std::string, blockInfo>);
public:

	Mesh chunk_mesh_;
	void update_mesh(std::vector<ChunkSection> data);
	void delete_block(glm::vec3);
	void draw(Shader* shader);
	ChunkRender(Database*, Chunk*);
	~ChunkRender();
};

