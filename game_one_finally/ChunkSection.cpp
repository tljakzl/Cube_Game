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
	int delta_x = 0;
	int delta_z = 0;

	if(position.x < 0 && position.z < 0)
	{
		delta_x = 1;
		delta_z = 1;
	}

	if (position.x < 0 && position.z > 0)
	{
		pos.z -= chunk_section_size_z;
		delta_x = 1;
	}
	if (position.x > 0 && position.z < 0)
	{
		pos.x -= chunk_section_size_x;
		delta_z = 1;
	}
		
	if (position.x > 0 && position.z > 0)
	{
		pos.x -= chunk_section_size_x ;
		pos.z -= chunk_section_size_z ;

	}


	for (auto y = 0; y < chunk_section_size_y; ++y)
	{
		for (auto z = 0; z < chunk_section_size_z; ++z)
		{
			for (auto x = 0; x < chunk_section_size_x; ++x)
			{
				blockInfo block;
				block.position_ = glm::vec3(x , y, z ) + pos;
				if(y == chunk_section_size_y - 1)
					block.indices.push_back(top_side);

				if (x == chunk_section_size_x - 1)
					block.indices.push_back(right_side);

				if (z == chunk_section_size_z - 1)
					block.indices.push_back(forward_side);

				if (y == 0)
					block.indices.push_back(bottom_side);

				if (x == 0)
					block.indices.push_back(left_side);


				
				


				if (z == 0)
					block.indices.push_back(backward_side);



				block.notempty = true;
				block.type_ = 1;
				std::string key = std::to_string(static_cast<int>(block.position_.x + delta_x)) + "x" + std::to_string(static_cast<int>(block.position_.y)) + "x" + std::to_string(static_cast<int>(block.position_.z + delta_z));
				chunk_section_data.emplace(key,block);

			}
		
		}
	
	}
}





