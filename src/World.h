#pragma once
#include "RenderMaster.h"
#include "MasterChunk.h"
#include <mutex>

class World
{

public:

	explicit World(Database* database);
	virtual ~World() = default;

	void Draw(Shader* shader);
	void DeleteBlock(const glm::vec3& pos);
	ChunkManager& GetChunkManager();
	RenderMaster& GetRenderMaster();
	const ChunkManager& GetChunkManager() const;
	const RenderMaster& GetRenderMaster() const;

private:
	Database* _database;
	std::mutex _mutex;
	RenderMaster _renderMaster;
	ChunkManager _chunkManager;
};

