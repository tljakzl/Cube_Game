#pragma once
#include "Model.h"
#include "ChunkRender.h"

class Chunk
{

	Mesh chunk;
	void render();


	unsigned size_x = 16;
	unsigned size_y = 16;
	unsigned size_z = 16;

	glm::vec3 chunk_position = { 0.0f,0.0f,0.0f };

	Database* database_;

public:
	
	void draw(Shader shader);
	Chunk(Database* database):database_(database)
	{
		render();
	}
	Chunk(ChunkRender chunk_render, Database* database,glm::vec3 position_chunk);
	~Chunk();
};

