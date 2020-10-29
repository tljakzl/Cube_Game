#pragma once
#include <vector>
#include "Database.h"
#include "Chunk.h"
#include "ChunkInfo.h"
#include <unordered_map>


class ChunkManager
{
	//std::pair<std::pair<int, int>, std::pair<int, int>> size_area({ -1,-1 }, { 1,1 });
	int x0 = -10;
	int x1 = 10;
	int z0 = -10;
	int z1 = 10;
	void add_face_in_area();
public:
	std::unordered_map<std::string,Chunk> area;
	ChunkManager();
	~ChunkManager();
	void create_area();
};

