#pragma once
#include "glm/detail/type_vec3.hpp"
#include <vector>


enum blockSide
{
	forward_side,
	backward_side,
	top_side,
	bottom_side,
	left_side,
	right_side
};

struct blockInfo
{
	glm::vec3 position_;
	short type_;
	std::vector<blockSide> indices;
	bool notempty = false;
};
