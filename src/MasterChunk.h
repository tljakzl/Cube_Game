#pragma once
#include <vector>
#include "Database.h"
#include "Chunk.h"
#include "ChunkInfo.h"
#include <unordered_map>
#include "RenderMaster.h"


class ChunkManager
{
    std::unordered_map<std::string,Chunk> area;
	int x0 = -10;
	int x1 = 10;
	int z0 = -10;
	int z1 = 10;

public:
    std::unordered_map<std::string,Chunk>& GetArea();
	ChunkManager();
	~ChunkManager();
	void create_area();
    void add_face_in_area(RenderMaster& render);
};

