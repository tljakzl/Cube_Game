#include "pch.h"
#include "ChunkSection.h"


blockInfo* ChunkSection::get_block(glm::vec3 pos_block)
{

	int x = static_cast<int>(abs(pos_block.x)) % 16;
	int z = static_cast<int>(abs(pos_block.z)) % 16;
	int y = static_cast<int>(abs(pos_block.y)) % 16;


	if (pos_block.x < 0)
		x = static_cast<int>(pos_block.x) % 16 + 15;
	
	if (pos_block.z < 0)
		z = static_cast<int>(pos_block.z) % 16 + 15;



	int key =  x + y * chunk_section_size_z*chunk_section_size_x +  z * chunk_section_size_z;
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

 
				if(block.position_.y == chunk_section_size_y - 1)
					block.indices.push_back(top_side);
				//if (x == chunk_section_size_x - 1)
				//	block.indices.push_back(right_side);
				//if (z == chunk_section_size_z - 1)
				//	block.indices.push_back(forward_side);
				//if (y == 0)
				//	block.indices.push_back(bottom_side);
				//if (x == 0)
				//	block.indices.push_back(left_side);
				//if (z == 0)
				//	block.indices.push_back(backward_side);



				block.notempty = true;
				block.type_ = 1;
				chunk_section_data.push_back(block);

			}
		
		}
	
	}
}





