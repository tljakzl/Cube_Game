#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(glm::vec3 position):chunk_position(position)
{
	glm::vec3 current_pos_section = chunk_position;
	for (auto curr_section = 0; curr_section < section_in_chunk; ++curr_section)
	{
		this->chunk_data.emplace_back(current_pos_section);
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
	return this->chunk_data.at(find_section(vec)).get_block(vec);
}

void Chunk::delete_block(glm::vec3 pos_block)
{
	get_block(pos_block)->notempty = false;
}