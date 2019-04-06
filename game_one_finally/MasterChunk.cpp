#include "pch.h"
#include "MasterChunk.h"



MasterChunk::MasterChunk()
{
}


MasterChunk::~MasterChunk()
{
}



void MasterChunk::create_area(Database* database, int x, int z)
{
	this->size_x = x;
	this->size_z = z;
	for (auto j = 0; j < z; ++j) 
	{
		std::vector<Chunk> vector_chunk;
		chunk_position.x = j * 16;
		for (auto i = 0; i < x; ++i)
		{
			ChunkRender chunk;
			chunk_position.z = i * 16;
			Chunk chunk_chunk(chunk, database, chunk_position);
			vector_chunk.push_back(chunk_chunk);
		}
		this->area.push_back(vector_chunk);
	}


}




void MasterChunk::draw(Shader shader)
{
	for (auto i = this->area.begin(); i < this->area.end(); ++i)
		for (auto j = i->begin(); j < i->end(); ++j)
			j->draw(shader);
}
