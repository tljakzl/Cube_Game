#include "pch.h"
#include "ChunkRender.h"


ChunkRender::ChunkRender(Database* database,Chunk* chunk)
    :database_(database)
    ,chunk_(chunk)
{
	for (const auto& curr_section : chunk_->chunk_data)
		render(curr_section.chunk_section_data);
	setup_mesh();
}

void ChunkRender::render(const std::vector<blockInfo>& curr_section)
{
	auto data_ver = database_->GetVertices();

	for (auto& x : curr_section) {
		if (x.notempty) {
			for (auto& cur_ind : x.indices) {
				for (auto i = 0; i < 6; ++i) {
					Vertex temp_ver;
					auto& dataVer = data_ver.at(cur_ind * 6 + i);
					temp_ver.Position = dataVer.Position + x.position_;
					temp_ver.Normal = dataVer.Normal;
					temp_ver.TexCoords = dataVer.TexCoords;

					_chunkMesh.AddVertices(temp_ver);
					_chunkMesh.AddIndices(block_count++);
				}
			}
		}
	}


	




	

	/*for (auto x : curr_section)
		if (x.second.notempty)
		{
			for (auto k : data_ver)
			{
				Vertex temp_ver;
				temp_ver.Position = k.Position + x.second.position_;
				temp_ver.Normal = k.Normal;
				temp_ver.TexCoords = k.TexCoords;
				this->_chunkMesh.vertices.push_back(temp_ver);

				for (auto cur_ind : x.second.indices)
				{
					for (auto number_point = 0; number_point < 6; ++number_point)
						this->_chunkMesh.indices.push_back(cur_ind * 6 + number_point + block_count);

				}
			}
			block_count += 36;
		}*/
	
	
}

void ChunkRender::setup_mesh()
{
	_chunkMesh.setTexture(&database_->textures_loaded);
	_chunkMesh.Setup();
}


void ChunkRender::draw(Shader* shader)
{
	_chunkMesh.Draw(shader);
}


void ChunkRender::update_mesh(const std::vector<ChunkSection>& data)
{
	block_count = 0;
	_chunkMesh.ClearData();
	_chunkMesh.ClearVertices();
	_chunkMesh.ClearIndices();

	for (auto& curr_section : data)
		render(curr_section.chunk_section_data);
	setup_mesh();
}



