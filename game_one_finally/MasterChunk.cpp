#include "pch.h"
#include "MasterChunk.h"



ChunkManager::ChunkManager()
{
}


ChunkManager::~ChunkManager()
{
}

void ChunkManager::create_area()
{
	glm::vec3 cur_chunk_pos = chunk_position_;
	for (auto j = x0; j <= x1 ; ++j)
	{
		if (j == 0 )
		{
			++j;
		}
		cur_chunk_pos.x = j   * chunk_section_size_x;
		for (auto i = z0; i <= z1 ; ++i)
		{
			if (i == 0) ++i;
				cur_chunk_pos.z = i  * chunk_section_size_z;
				//Chunk chunk(cur_chunk_pos);
				std::string key = std::to_string(j) + "x" + std::to_string(i);
				area.emplace(key, cur_chunk_pos);
			
			
		
	
		}
	}
}
