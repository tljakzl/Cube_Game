#include "pch.h"
#include "World.h"


std::string find_chunk(glm::vec3 pos)
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

World::World(Database* database):database_(database)
{
	world.create_area();
	for (auto curr_chunk : world.area)
	{
		ChunkRender rend_chunk(database_, &curr_chunk.second);
		render.add_chunk(curr_chunk.first ,rend_chunk);
	}
	
}


World::~World()
{
}

void World::draw(Shader* shader)
{
	this->render.draw_chunks(shader);
}


void World::delete_block(glm::vec3 pos)
{
	std::string key = find_chunk(pos);
	glm::vec3 pos_left = { pos.x + 1, pos.y, pos.z };
	std::string key_left = find_chunk(pos_left);

	glm::vec3 pos_right = { pos.x - 1, pos.y, pos.z };
	std::string key_right = find_chunk(pos_right);

	glm::vec3 pos_forward = { pos.x , pos.y, pos.z - 1};
	std::string key_forward = find_chunk(pos_forward);

	glm::vec3 pos_backward = { pos.x , pos.y, pos.z + 1 };
	std::string key_backward = find_chunk(pos_backward);

	glm::vec3 pos_top = { pos.x , pos.y - 1, pos.z  };
	std::string key_top = find_chunk(pos_top);

	glm::vec3 pos_bottom = { pos.x , pos.y + 1, pos.z };
	std::string key_bottom = find_chunk(pos_bottom);
	
	try
	{
		world.area.at(key).delete_block(pos);
		try 
		{
			world.area.at(key_top).get_block(pos_top)->indices.push_back(top_side);
		}
		catch (std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}


		try
		{
			world.area.at(key_bottom).get_block(pos_bottom)->indices.push_back(bottom_side);
		}
		catch (std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}

		try 
		{
			world.area.at(key_left).get_block(pos_left)->indices.push_back(left_side);
			if (key != key_left)
				render.update_chunk(key_left, world.area.at(key_left).chunk_data);
		}
		catch(std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}


		try {
			world.area.at(key_right).get_block(pos_right)->indices.push_back(right_side);
			if (key != key_right)
				render.update_chunk(key_right, world.area.at(key_right).chunk_data);
		}
		catch (std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}
		

		try
		{
			world.area.at(key_forward).get_block(pos_forward)->indices.push_back(forward_side);
			if (key != key_forward)
				render.update_chunk(key_forward, world.area.at(key_forward).chunk_data);
		}
		catch (std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}


		try
		{
			world.area.at(key_backward).get_block(pos_backward)->indices.push_back(backward_side);
			if (key != key_backward)
				render.update_chunk(key_backward, world.area.at(key_backward).chunk_data);
		}
		catch (std::out_of_range err)
		{
			std::cout << err.what() << std::endl;
		}


		
			
		

		//need add top and bottom, and add function for update 
	
		render.update_chunk(key, world.area.at(key).chunk_data);

	}
	catch (...)
	{
		throw;
	}
}



