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

	add_face_in_area();

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





void ChunkManager::add_face_in_area()
{
	for (auto cur_chunk: this->area)
	{
		for (auto section:cur_chunk.second.chunk_data)
		{
			for (auto block:section.chunk_section_data)
			{
				if (block.notempty == false)
				{
					
					GLfloat x = block.position_.x + 0.5;
					GLfloat y = block.position_.y;
					GLfloat z = block.position_.z + 0.5;
				
					glm::vec3 pos = { x,y,z };



					glm::vec3 pos_top = { pos.x , pos.y - 1, pos.z };
					std::string key_top = findd_chunk(pos_top);

					glm::vec3 pos_bottom = { pos.x , pos.y + 1, pos.z };
					std::string key_bottom = findd_chunk(pos_bottom);

					glm::vec3 pos_left = { pos.x + 1 , pos.y , pos.z };
					std::string key_left = findd_chunk(pos_left);

					glm::vec3 pos_right = { pos.x - 1 , pos.y , pos.z };
					std::string key_right = findd_chunk(pos_right);

					glm::vec3 pos_forward = { pos.x  , pos.y , pos.z - 1 };
					std::string key_forward = findd_chunk(pos_forward);

					glm::vec3 pos_backward = { pos.x  , pos.y , pos.z + 1 };
					std::string key_backward = findd_chunk(pos_backward);

					
						try
						{
							auto block_top = area.at(key_top).get_block(pos_top);
							if (block_top->notempty == true)
								block_top->indices.push_back(top_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}


						try
						{
							auto block_bottom = area.at(key_bottom).get_block(pos_bottom);
							if (block_bottom->notempty == true)
								block_bottom->indices.push_back(bottom_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}


						try
						{
							auto block_left = area.at(key_left).get_block(pos_left);
							if (block_left->notempty == true)
								block_left->indices.push_back(left_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}



						try
						{
							auto block_forward = area.at(key_forward).get_block(pos_forward);
							if (block_forward->notempty == true)
								block_forward->indices.push_back(forward_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}

						try
						{
							auto block_backward = area.at(key_backward).get_block(pos_backward);
							if (block_backward->notempty == true)
								block_backward->indices.push_back(backward_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}

						try
						{
							auto block_right = area.at(key_right).get_block(pos_right);
							if (block_right->notempty == true)
								block_right->indices.push_back(right_side);
						}
						catch (std::out_of_range err)
						{
							//std::cout << err.what() << std::endl;
						}




					
				

				

				}
			}
		}
	}

}




