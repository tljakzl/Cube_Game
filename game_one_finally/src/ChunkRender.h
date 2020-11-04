#pragma once
#include "Mesh.h"
#include "Database.h"
#include "Chunk.h"


class ChunkRender
{
public:
	void update_mesh(const std::vector<ChunkSection>& data);
	void delete_block(glm::vec3);
	void draw(Shader* shader);
	ChunkRender(Database*, Chunk*);
private:
    void render(const std::vector<blockInfo>&);
    void setup_mesh();
private:
    int block_count = 0;
    Database* database_;
    Chunk* chunk_;
    Mesh _chunkMesh;
};

