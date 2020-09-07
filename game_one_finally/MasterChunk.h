#pragma once
#include <vector>
#include "Database.h"
#include "Chunk.h"
#include "ChunkInfo.h"
#include <unordered_map>


class ChunkManager
{
	//std::pair<std::pair<int, int>, std::pair<int, int>> size_area({ -1,-1 }, { 1,1 });
	int x0 = -3;
	int x1 = 3;
	int z0 = -3;
	int z1 = 3;
	void add_face_in_area();
public:
	std::unordered_map<std::string,Chunk> area;
	ChunkManager();
	~ChunkManager();
	void create_area();
};

