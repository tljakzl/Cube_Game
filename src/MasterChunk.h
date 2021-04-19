#pragma once
#include <vector>
#include <unordered_map>
#include "Database.h"
#include "Chunk.h"
#include "ChunkInfo.h"
#include "RenderMaster.h"

class ChunkManager
{
public:

	ChunkManager() = default;
	~ChunkManager() = default;
	void CreateArea();
    std::unordered_map<std::string,Chunk>& GetArea();
    void AddFaceInArea(RenderMaster& render);

private:
    int _x0 = -10;
    int _z0 = -10;
    int _x1 = 10;
    int _z1 = 10;
    std::unordered_map<std::string,Chunk> _area;
};

