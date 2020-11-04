#pragma once
#include "RenderMaster.h"
#include "MasterChunk.h"
#include <mutex>

class World
{

public:
	ChunkManager world;
	World(Database* database);
	void draw(Shader* shader);
	void delete_block(glm::vec3 pos);
	~World();
    std::mutex _mutex;
    RenderMaster render;
private:
    Database* database_;


};

