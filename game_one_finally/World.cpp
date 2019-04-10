#include "pch.h"
#include "World.h"


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

void World::draw(Shader shader)
{
	this->render.draw_chunks(shader);
}


void World::delete_block(glm::vec3 pos)
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

	std::string key = std::to_string(chunk_x) + "x" + std::to_string(chunk_z);
	
	try
	{
		world.area.at(key).delete_block(pos);
		render.update_chunk(key, world.area.at(key).chunk_data);
	}
	catch (...)
	{
		throw;
	}
}
