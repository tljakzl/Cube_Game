#include "pch.h"
#include "ChunkRender.h"


ChunkRender::ChunkRender(Database* database,Chunk* chunk):database_(database),chunk_(chunk)
{
	for (const auto curr_section : chunk_->chunk_data)
		render(curr_section.chunk_section_data);
}


ChunkRender::~ChunkRender()
{
}

void ChunkRender::render(std::unordered_map<std::string,blockInfo> curr_section)
{
	auto data_ver = database_->data.begin()->vertices;

	auto block_count = 0;

	Mesh temp_mesh;

	for (auto x : curr_section)
		if (x.second.notempty)
		{
			for (auto k : data_ver)
			{
				Vertex temp_ver;
				temp_ver.Position = k.Position + x.second.position_;
				temp_ver.Normal = k.Normal;
				temp_ver.TexCoords = k.TexCoords;
				temp_mesh.vertices.push_back(temp_ver);

				for (auto cur_ind : x.second.indices)
				{
					for (auto number_point = 0; number_point < 6; ++number_point)
						temp_mesh.indices.push_back(cur_ind * 6 + number_point + block_count);

				}
			}
			block_count += 36;
		}
	temp_mesh.textures = &database_->textures_loaded;
	temp_mesh.setupMesh();
	this->chunk_mesh_.push_back(temp_mesh);
}



void ChunkRender::draw(Shader shader)
{
	for (auto cur_mesh : chunk_mesh_)
		cur_mesh.Draw(shader);
}


void ChunkRender::update_mesh(std::vector<ChunkSection> data)
{

	for (auto curr_section : chunk_mesh_)
		curr_section.clear_data();

	this->chunk_mesh_.clear();
	this->chunk_mesh_.shrink_to_fit();

	for (auto curr_section : data)
		render(curr_section.chunk_section_data);
}



