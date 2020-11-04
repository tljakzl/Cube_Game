#include "pch.h"
#include "getter_block.h"
#include <iterator>


bool getter_block::iter_up_x()
{

	if ((abs(std::distance(x_i, data->begin())) + 1) % chunk_section_size_x != 0)
	{
		++x_i;
		return true;
	}
	return false;
}

bool getter_block::iter_down_x()
{
	if ((abs(std::distance(x_i, data->begin()))) % chunk_section_size_x != 0)
	{
		--x_i;
		return true;
	}
	
	/*if ()
		{
			return true;
		}*/
		
	
	return false;
}

bool getter_block::iter_up_z()
{
	if ((abs(std::distance(x_i, data->begin()))) % (chunk_section_size_z * chunk_section_size_x) < chunk_section_size_x * (chunk_section_size_z - 1))
	{
		x_i += chunk_section_size_z;
		return true;
	}
	return false;
}

bool getter_block::iter_down_z()
{
	if ((abs(std::distance(x_i, data->begin()))) % (chunk_section_size_z * chunk_section_size_x) > chunk_section_size_x)
	{
		x_i -= chunk_section_size_z;
		return true;
	}
	return false;
}

bool getter_block::iter_up_y()
{
	if (std::distance(x_i, data->end()) > chunk_section_size_x *chunk_section_size_z)
	{
		x_i += chunk_section_size_x * chunk_section_size_z;
		return true;
	}
	return false;
}

bool getter_block::iter_down_y()
{
	if (abs(std::distance(x_i, data->begin())) > chunk_section_size_x * chunk_section_size_z)
	{
		x_i -= chunk_section_size_x * chunk_section_size_z;
		return true;
	}
	return false;
}


void getter_block::update_around_block()
{
	_up_x(*this);
	_down_x(*this);
	_up_y(*this);
	_down_y(*this);
	_up_z(*this);
	_down_z(*this);


}
void getter_block::_up_x(getter_block iterator)
{
	if (iterator.iter_up_x())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(left_side);
}

void getter_block::_down_x(getter_block iterator)
{
	if (iterator.iter_down_x())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(right_side);
}

void getter_block::_up_z(getter_block iterator)
{
	if (iterator.iter_up_z())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(backward_side);
}

void getter_block::_down_z(getter_block iterator)
{
	if (iterator.iter_down_z())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(forward_side);
}

void getter_block::_up_y(getter_block iterator)
{
	if (iterator.iter_up_y())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(bottom_side);
}

void getter_block::_down_y(getter_block iterator)
{
	if (iterator.iter_down_y())
		if (iterator.x_i->notempty)
			iterator.x_i->indices.push_back(top_side);
}


