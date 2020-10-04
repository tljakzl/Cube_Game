#pragma once
#include <vector>
#include "glm/detail/type_vec3.hpp"
#include "BlockInfo.h"
#include "ChunkInfo.h"
#include <unordered_map>

class ChunkSection
{

	void render(glm::vec3);

public:

	std::vector<blockInfo> chunk_section_data;
	blockInfo* get_block(glm::vec3);
	ChunkSection(glm::vec3 position);
	~ChunkSection();
};

