#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(glm::vec3 position)
    :chunk_position(position)
{
	glm::vec3 current_pos_section = chunk_position;
	for (int curr_section = 0; curr_section < section_in_chunk; ++curr_section)
	{
		chunk_data.emplace_back(current_pos_section);
		current_pos_section.y += chunk_section_size_y;
	}

}

Chunk::~Chunk()
{
}

int Chunk::find_section(glm::vec3 pos_block)
{
	return static_cast<int>(pos_block.y / chunk_section_size_y) ;
}

blockInfo* Chunk::get_block(const glm::vec3& vec)
{
    if(int section = find_section(vec); section < section_in_chunk)
    {
        return chunk_data.at(section).get_block(vec);
    }
    else
    {
        return nullptr;
    }
}

void Chunk::delete_block(glm::vec3 pos_block)
{
	get_block(pos_block)->notempty = false;
}