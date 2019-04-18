#include "pch.h"
#include "ChunkRender.h"


ChunkRender::ChunkRender(Database* database,Chunk* chunk):database_(database),chunk_(chunk)
{
	for (const auto curr_section : chunk_->chunk_data)
		render(curr_section.chunk_section_data);
	setup_mesh();
}


ChunkRender::~ChunkRender()
{
}

void ChunkRender::render(std::vector<blockInfo> curr_section)
{
	auto data_ver = database_->data.begin()->vertices;

	for (auto x : curr_section) 
	{
		if (x.notempty)
		{
			for (auto cur_ind : x.indices)
			{
				for (auto i = 0; i < 6; ++i)
				{
					Vertex temp_ver;
					temp_ver.Position = data_ver.at(cur_ind * 6 + i).Position + x.position_;
					temp_ver.Normal = data_ver.at(cur_ind * 6 + i).Normal;
					temp_ver.TexCoords = data_ver.at(cur_ind * 6 + i).TexCoords;

					this->chunk_mesh_.vertices.push_back(temp_ver);
					this->chunk_mesh_.indices.push_back(block_count++);
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
				this->chunk_mesh_.vertices.push_back(temp_ver);

				for (auto cur_ind : x.second.indices)
				{
					for (auto number_point = 0; number_point < 6; ++number_point)
						this->chunk_mesh_.indices.push_back(cur_ind * 6 + number_point + block_count);

				}
			}
			block_count += 36;
		}*/
	
	
}

void ChunkRender::setup_mesh()
{
	this->chunk_mesh_.textures = &database_->textures_loaded;
	this->chunk_mesh_.setupMesh();
}


void ChunkRender::draw(Shader* shader)
{
	this->chunk_mesh_.Draw(shader);
}


void ChunkRender::update_mesh(std::vector<ChunkSection> data)
{
	block_count = 0;
	this->chunk_mesh_.clear_data();
	this->chunk_mesh_.indices.clear();
	this->chunk_mesh_.indices.shrink_to_fit();
	this->chunk_mesh_.vertices.clear();
	this->chunk_mesh_.vertices.shrink_to_fit();

	for (auto curr_section : data)
		render(curr_section.chunk_section_data);
	setup_mesh();
}



