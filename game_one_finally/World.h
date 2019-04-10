#pragma once
#include "RenderMaster.h"
#include "MasterChunk.h"

class World
{
	Database* database_;
public:

	RenderMaster render;
	ChunkManager world;
	World(Database* database);
	void draw(Shader shader);
	~World();
};

