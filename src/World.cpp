#include "pch.h"
#include "World.h"

World::World(Database* database)
    : _database(database)
    , _mutex()
{
    _chunkManager.CreateArea();
    for (auto& curr_chunk : _chunkManager.GetArea())
    {
        ChunkRender rend_chunk(_database, &curr_chunk.second);
        _renderMaster.AddChunk(curr_chunk.first , std::move(rend_chunk));
    }
}

const ChunkManager &World::GetChunkManager() const {
    return _chunkManager;
}

const RenderMaster &World::GetRenderMaster() const {
    return _renderMaster;
}

ChunkManager& World::GetChunkManager() {
    return _chunkManager;
}

RenderMaster &World::GetRenderMaster() {
    return _renderMaster;
}

void World::Draw(Shader* shader)
{
    std::unique_lock<std::mutex> lock {_mutex};
    if(lock)
    {
        _renderMaster.DrawChunks(shader);
    }
}


void World::DeleteBlock(const glm::vec3& pos)
{
	std::string key = GetChunkManager().FindChunk(pos);
	glm::vec3 pos_left = { pos.x + 1, pos.y, pos.z };
	std::string key_left = GetChunkManager().FindChunk(pos_left);

	glm::vec3 pos_right = { pos.x - 1, pos.y, pos.z };
	std::string key_right = GetChunkManager().FindChunk(pos_right);

	glm::vec3 pos_forward = { pos.x , pos.y, pos.z - 1 };
	std::string key_forward = GetChunkManager().FindChunk(pos_forward);

	glm::vec3 pos_backward = { pos.x , pos.y, pos.z + 1 };
	std::string key_backward = GetChunkManager().FindChunk(pos_backward);

	glm::vec3 pos_top = { pos.x , pos.y - 1, pos.z };
	std::string key_top = GetChunkManager().FindChunk(pos_top);

	glm::vec3 pos_bottom = { pos.x , pos.y + 1, pos.z };
	std::string key_bottom = GetChunkManager().FindChunk(pos_bottom);


	auto& area = GetChunkManager().GetArea();
	auto found = area.find(key);

	if (found != area.end())
	{
		auto& chunk = found->second;
		auto block_to_delete = chunk.get_block(pos);
		if (block_to_delete != nullptr)
		{
			block_to_delete->notempty = false;

			//chunk.delete_block(pos);
			auto push_side = [&](glm::vec3 pos, blockSide side) { if (chunk.get_block(pos) != nullptr) { chunk.get_block(pos)->indices.push_back(side); } };
			push_side(pos_top, top_side);
			push_side(pos_bottom, bottom_side);
			push_side(pos_left, left_side);
			push_side(pos_right, right_side);
			push_side(pos_forward, forward_side);
			push_side(pos_backward, backward_side);

			if (key != key_backward && area.count(key_backward))
				GetRenderMaster().UpdateChunk(key_backward, area.at(key_backward).chunk_data);
			if (key != key_left && area.count(key_left))
				GetRenderMaster().UpdateChunk(key_left, GetChunkManager().GetArea().at(key_left).chunk_data);
			if (key != key_forward && area.count(key_forward))
				GetRenderMaster().UpdateChunk(key_forward, GetChunkManager().GetArea().at(key_forward).chunk_data);
			if (key != key_right && area.count(key_right))
				GetRenderMaster().UpdateChunk(key_right, GetChunkManager().GetArea().at(key_right).chunk_data);


			GetRenderMaster().UpdateChunk(key, chunk.chunk_data);

		}
	}

	

}
