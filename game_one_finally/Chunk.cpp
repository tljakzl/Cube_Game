#include "pch.h"
#include "Chunk.h"



Chunk::Chunk(ChunkRender chunk_render,Database* database,glm::vec3 position):chunk_position(position)
{
	
	auto data_ver  = database->data.begin()._Ptr->vertices;
	auto chunk_data = chunk_render.chunk_data;
	auto block_count = 0;
	for (auto y = chunk_data.begin(); y < chunk_data.end(); ++y)
		for (auto z = y->begin(); z < y->end(); ++z)
			for (auto x = z->begin(); x < z->end(); ++x)
				if (x->notempty)
				{
					for (auto k = data_ver.begin(); k < data_ver.end(); ++k)
					{
						Vertex temp_ver;
						temp_ver.Position = k->Position + chunk_position + x->position_;
						temp_ver.Normal = k->Normal;
						temp_ver.TexCoords = k->TexCoords;
						chunk.vertices.push_back(temp_ver);

						for (auto cur_ind = x->indices.begin(); cur_ind < x->indices.end(); ++cur_ind)
						{
							for (auto number_point = 0; number_point < 6; ++number_point)
								chunk.indices.push_back(*cur_ind * 6 + number_point + block_count);
							
						}
						

							
					}
					block_count += 36;
				}
	chunk.textures = &database->textures_loaded;
	chunk.setupMesh();
}




Chunk::~Chunk()
{
}


void Chunk::render()
{
	//std::vector<unsigned> sides;
	//sides.push_back(1);
	//sides.push_back(0);

	//glDisable(GL_BLEND);
	

	

	int m = 0;
	auto data = database_->data.begin()._Ptr;
	for (auto y = 0; y < size_y; ++y)
		for (auto x = 0; x < size_x; ++x)
		{

			for (auto z = 0; z < size_z; ++z)
			{
			
					for (auto i = data->vertices.begin(); i < data->vertices.end(); ++i)
					{
						Vertex temp_ver;
						temp_ver.Position = i._Ptr->Position + chunk_position + glm::vec3(x,y,z);
						temp_ver.Normal = i._Ptr->Normal;
						temp_ver.TexCoords = i._Ptr->TexCoords;
						chunk.vertices.push_back(temp_ver);
					}

					for (auto b = 0; b < 36;b++)
						chunk.indices.push_back(m++);
				
			
			}

		}

	chunk.textures = data->textures;
	chunk.setupMesh();
}

void Chunk::draw(Shader shader)
{
	
	chunk.Draw(shader);
	
}


