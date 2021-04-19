#include "pch.h"
#include "MasterChunk.h"

void ChunkManager::CreateArea()
{
	glm::vec3 cur_chunk_pos = chunk_position_;
	for (auto j = _x0; j <= _x1 ; ++j)
	{
		if (j == 0 ){
			++j;
		}
		cur_chunk_pos.x = j   * chunk_section_size_x;
		for (auto i = _z0; i <= _z1 ; ++i) {
            if (i == 0) {
                ++i;
            }
            cur_chunk_pos.z = i * chunk_section_size_z;
            std::string key = std::to_string(j) + "x" + std::to_string(i);
            _area.emplace(key, cur_chunk_pos);
        }
	}
}

std::string FindChunk(glm::vec3 pos)
{
    int counter = 0;
	float num_x = pos.x / 16;
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

void ChunkManager::AddFaceInArea(RenderMaster& render)
{
    auto&& addSide = [this](const glm::vec3&& pos, blockSide side){
        if (auto&& foundBlock = _area.find(FindChunk(pos)); foundBlock != _area.end())
        {
            if (auto&& block = foundBlock->second.get_block(pos); block && block->notempty) {
                block->indices.push_back(side);
            }
        }
    };

	for (auto& cur_chunk : _area)
	{
		for (auto& section : cur_chunk.second.chunk_data)
		{
			for (auto& block : section.chunk_section_data)
			{
				if (!block.notempty){
					glm::vec3 pos(block.position_ + glm::vec3(.5f, 0.f, .5f));

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
        render.UpdateChunk(cur_chunk.first, cur_chunk.second.chunk_data);
	}
}

std::unordered_map<std::string, Chunk> &ChunkManager::GetArea() {
    return _area;
}




