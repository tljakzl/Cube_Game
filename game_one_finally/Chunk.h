#pragma once
#include "Model.h"
#include "ChunkSection.h"
#include "ChunkInfo.h"

class Chunk
{

public:
	std::vector<ChunkSection> chunk_data;
	glm::vec3 chunk_position;
	int x;
	int z;
	blockInfo* get_block(glm::vec3);
	void delete_block(glm::vec3 pos_block);
	Chunk(glm::vec3 position_chunk);
	~Chunk();
	int find_section(glm::vec3 pos_block);
	
};

