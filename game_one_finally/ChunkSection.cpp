#include "pch.h"
#include <iterator>
#include "getter_block.h"
#include "ChunkSection.h"
#include <string>


blockInfo* ChunkSection::get_block(glm::vec3 pos_block)
{
	std::string key = std::to_string(static_cast<int>(pos_block.x)) + "x" + std::to_string(static_cast<int>(pos_block.y)) + "x" + std::to_string(static_cast<int>(pos_block.z));
	auto *block = &chunk_section_data.at(key);
	return block;
}

ChunkSection::ChunkSection(glm::vec3 position)
{
	render(position);
}


ChunkSection::~ChunkSection()
{
}



void ChunkSection::render(glm::vec3 position)
{
	glm::vec3 pos = position;
	int x_start = 0;
	int z_start = 0;
	if (position.x < 0 && position.z > 0)
		pos.z -= chunk_section_size_z;
	if (position.x > 0 && position.z < 0)
		pos.x -= chunk_section_size_x;
		
	if (position.x > 0 && position.z > 0)
	{
		pos.x -= chunk_section_size_x;
		pos.z -= chunk_section_size_z;
	}


	for (auto y = 0; y < chunk_section_size_y; ++y)
	{
		for (auto z = z_start; z < chunk_section_size_z; ++z)
		{
			for (auto x = x_start; x < chunk_section_size_x; ++x)
			{
				blockInfo block;
				block.position_ = glm::vec3(x, y, z) + pos;
				block.indices.push_back(top_side);
				block.notempty = true;
				block.type_ = 1;
				std::string key = std::to_string(static_cast<int>(block.position_.x)) + "x" + std::to_string(static_cast<int>(block.position_.y)) + "x" + std::to_string(static_cast<int>(block.position_.z));
				chunk_section_data.emplace(key,block);

			}
		
		}
	
	}
}





