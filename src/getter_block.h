#pragma once
#include <vector>
#include "BlockInfo.h"
#include "ChunkInfo.h"
#include "ChunkSection.h"

class getter_block
{
	using value_type = blockInfo;

	//using pointer = const value_type*;
	//using reference = const value_type&;

	typedef  std::vector<value_type> container;
	typedef  std::vector<ChunkSection> area;
	typedef container::iterator cont_iter;



	void _up_x(getter_block iterator);
	void _up_y(getter_block iterator);
	void _up_z(getter_block iterator);
	void _down_x(getter_block iterator);
	void _down_y(getter_block iterator);
	void _down_z(getter_block iterator);


public:
	area chunk_vector;
	container* data;
	cont_iter x_i;

	getter_block(area chunk_vector_,cont_iter x, container* data_) : chunk_vector(chunk_vector_),data(data_), x_i(x) {}
	~getter_block() = default;

	void update_around_block();

	bool iter_up_x();
	bool iter_down_x();
	bool iter_up_z();
	bool iter_down_z();
	bool iter_up_y();
	bool iter_down_y();
};

