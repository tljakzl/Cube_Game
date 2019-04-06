#include "pch.h"
#include "ChunkRender.h"
#include <iterator>


ChunkRender::ChunkRender()
{
	render();
}


ChunkRender::~ChunkRender()
{
}


void ChunkRender::set_indices_x(blockInfo* x1, blockInfo* x2)
{
	if (x1->notempty && !x2->notempty) x1->indices.push_back(right_side);
	if (x2->notempty && !x1->notempty) x2->indices.push_back(left_side);
}

void ChunkRender::set_indices_y(blockInfo* y1, blockInfo* y2)
{
	if (y1->notempty && !y2->notempty) y1->indices.push_back(top_side);
	if (y2->notempty && !y1->notempty) y2->indices.push_back(bottom_side);
}

void ChunkRender::set_indices_z(blockInfo* z1, blockInfo* z2)
{
	if (z1->notempty && !z2->notempty) z1->indices.push_back(forward_side);
	if (z2->notempty && !z1->notempty) z2->indices.push_back(backward_side);
}

void ChunkRender::render()
{
	for (auto y = 0; y < size_y; ++y)
	{
		std::vector<std::vector<blockInfo>> vec_z;
		for (auto z = 0; z < size_z; ++z)
		{
			std::vector<blockInfo> vec_x;
			for (auto x = 0; x < size_x; ++x)
			{
				blockInfo block;

				int  randx = rand() %15;
				int  randy = rand() %15;
				int  randz = rand() %15;
				if (x != randx && y != randy && z != randz && x != randz && y != randx && z != randy && x != randy && y != randz && z != randx)
				{

					if (x == 0) set_block(&block, left_side, glm::vec3(x, y, z), true);

					if (z == 0) set_block(&block, backward_side, glm::vec3(x, y, z), true);

					if (y == 0) set_block(&block, bottom_side, glm::vec3(x, y, z), true);

					if (x == size_x - 1) set_block(&block, right_side, glm::vec3(x, y, z), true);

					if (z == size_z - 1) set_block(&block, forward_side, glm::vec3(x, y, z), true);

					if (y == size_y - 1) set_block(&block, top_side, glm::vec3(x, y, z), true);


					block.position_ = glm::vec3(x, y, z);
					block.notempty = true;
					block.type_ = 1;


				}
				else
				{
					block.position_ = glm::vec3(x, y, z);
					block.notempty = false;
					block.type_ = 1;
				}

					vec_x.push_back(block);
			
			}
			vec_z.push_back(vec_x);
		}
		chunk_data.push_back(vec_z);
	}
	set_indices();
}

void ChunkRender::set_block(blockInfo* info , blockSide side, glm::vec3 pos, bool notempty)
{
	info->position_ = pos;
	info->notempty = notempty;
	info->type_ = 1;
	info->indices.push_back(side);
}

void ChunkRender::set_indices()
{
	
	
	/*auto  y = chunk_data.begin();
	auto  z = y->begin();
	auto  x = z->begin();
	block_psevdo_iterator iterator(x,y,z,&chunk_data);
	iterator.iter_up_y();
	iterator.ptr_->notempty = false;
	update_around_block(iterator);
	iterator.iter_up_y();
	iterator.ptr_->notempty = false;
	update_around_block(iterator);
	iterator.iter_up_y();
	iterator.iter_up_x();
	iterator.iter_up_z();
	iterator.iter_up_z();
	iterator.iter_up_z();
	iterator.ptr_->notempty = false;
	update_around_block(iterator);*/




	/*iterator.ptr_->notempty = false;
	update_around_block(iterator);*/



			
	
	for (auto y = chunk_data.begin(); y < chunk_data.end();++y)
	{
		for (auto z = y->begin(); z< y->end();++z)
		{
			for (auto x = z->begin(); x < z->end() ; ++x)
			{
			
				if (x->notempty == false)
				{
					block_psevdo_iterator iterator(x,y,z,&chunk_data);
					update_around_block(iterator);
				}
			}

		}
	}






}



blockInfo* ChunkRender::get_block(int x, int y, int z)
{
	return &this->chunk_data.at(y).at(z).at(x);

}


void ChunkRender::update_around_block(block_psevdo_iterator iterator)
{
	iter_up_x(iterator);
	iter_down_x(iterator);
	iter_up_y(iterator);
	iter_down_y(iterator);
	iter_up_z(iterator);
	iter_down_z(iterator);


}
void ChunkRender::iter_up_x(block_psevdo_iterator iterator)
{
	if (iterator.iter_up_x())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(left_side);
}

void ChunkRender::iter_down_x(block_psevdo_iterator iterator)
{
	if (iterator.iter_down_x())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(right_side);
}

void ChunkRender::iter_up_z(block_psevdo_iterator iterator)
{
	if (iterator.iter_up_z())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(backward_side);
}

void ChunkRender::iter_down_z(block_psevdo_iterator iterator)
{
	if (iterator.iter_down_z())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(forward_side);
}

void ChunkRender::iter_up_y(block_psevdo_iterator iterator)
{
	if (iterator.iter_up_y())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(bottom_side);
}

void ChunkRender::iter_down_y(block_psevdo_iterator iterator)
{
	if (iterator.iter_down_y())
		if (iterator.ptr_->notempty)
			iterator.ptr_->indices.push_back(top_side);
}


