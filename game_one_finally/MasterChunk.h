#pragma once
#include <vector>
#include "Database.h"
#include "Chunk.h"
#include "ChunkInfo.h"
#include <unordered_map>


class ChunkManager
{
	//std::pair<std::pair<int, int>, std::pair<int, int>> size_area({ -1,-1 }, { 1,1 });
	int x0 = -1;
	int x1 = 1;
	int z0 = -1;
	int z1 = 1;
public:
	std::unordered_map<std::string,Chunk> area;
	ChunkManager();
	~ChunkManager();
	void create_area();
};

