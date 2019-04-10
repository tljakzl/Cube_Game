#include "pch.h"
#include "World.h"


World::World(Database* database):database_(database)
{
	world.create_area();
	for (auto curr_chunk : world.area)
	{
		ChunkRender rend_chunk(database_, &curr_chunk.second);
		render.add_chunk(rend_chunk);
	}
	try 
	{
		world.area.at("4x3");
	}
	catch (std::out_of_range t)
	{
		std::cout << t.what() << std::endl;
		throw;
	}
}


World::~World()
{
}

void World::draw(Shader shader)
{
	this->render.draw_chunks(shader);
}
