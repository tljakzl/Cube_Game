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

std::string findd_chunk(glm::vec3 pos)
{
	float num_x = pos.x / 16;
	int counter = 0;
	float num_z = pos.z / 16;

	if (num_x >= 0)
		counter = 1;
	else counter = -1;
	int chunk_x = (int)(pos.x / 16) + counter;

	if (num_z >= 0)
		counter = 1;
	else counter = -1;
	int chunk_z = (int)(pos.z / 16) + counter;

	return  std::to_string(chunk_x) + "x" + std::to_string(chunk_z);
}

void ChunkManager::add_face_in_area(RenderMaster& render)
{
	for (auto& cur_chunk : area)
	{
		for (auto& section : cur_chunk.second.chunk_data)
		{
			for (auto& block : section.chunk_section_data)
			{
				if (!block.notempty){
					GLfloat x = block.position_.x + 0.5;
					GLfloat y = block.position_.y;
					GLfloat z = block.position_.z + 0.5;
				
					glm::vec3 pos = { x,y,z };

					auto&& addSide = [this](const glm::vec3& pos, blockSide side){

                        std::string key_top = findd_chunk(pos);
                        if (auto&& foundBlock = area.find(key_top); foundBlock != area.end())
                        {
                            if(auto&& block = foundBlock->second.get_block(pos)) {
                                if (block->notempty == true) {
                                    block->indices.push_back(side);
                                }
                            }
                        }
					};

                    addSide(glm::vec3(pos.x, pos.y - 1, pos.z), top_side);
                    addSide(glm::vec3(pos.x, pos.y + 1, pos.z), bottom_side);
                    addSide(glm::vec3(pos.x + 1, pos.y, pos.z), left_side);
                    addSide(glm::vec3(pos.x - 1, pos.y, pos.z), right_side);
                    addSide(glm::vec3(pos.x, pos.y, pos.z - 1), forward_side);
                    addSide(glm::vec3(pos.x, pos.y, pos.z + 1), backward_side);
				}
				else
                {
                    if(block.position_.y == 15) {
                        block.indices.push_back(top_side);
                    }
                }
			}
		}
        render.update_chunk(cur_chunk.first, cur_chunk.second.chunk_data);
	}
}

std::unordered_map<std::string, Chunk> &ChunkManager::GetArea() {
    return area;
}




