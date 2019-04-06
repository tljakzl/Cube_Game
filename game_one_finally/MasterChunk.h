#pragma once
#include <vector>
#include "Database.h"
#include "Chunk.h"


class MasterChunk
{
	std::vector<std::vector<Chunk>> area;
	Database* database;
	glm::vec3 chunk_position = { 0,0,0 };
	int size_x;
	int size_z;
public:
	void draw(Shader shader);
	MasterChunk();
	~MasterChunk();
	void create_area(Database* database, int x, int z);
};

