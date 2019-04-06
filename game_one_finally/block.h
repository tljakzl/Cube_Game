#pragma once
#include <vector>
#include "buffer_vertex_array.h"
#include <glm/detail/type_vec3.hpp>

class block
{

	GLfloat a = -1.0;
	GLfloat b = -0.984;

	std::vector<GLfloat> shape_ =
	{
		//BACKWARD
		0.0, 0.0, 0.0,		a, a,   //48 for 16 pix
		1.0, 0.0, 0.0,		b, a,
		1.0, 1.0, 0.0,		b, b,
		1.0, 1.0, 0.0,		b, b,
		0.0, 1.0, 0.0,		a, b,
		0.0, 0.0, 0.0,		a, a,

		// FORWARD
		0.0, 0.0, 1.0,		a, a,
		1.0, 0.0, 1.0,		b, a,
		1.0, 1.0, 1.0,		b, b,
		1.0, 1.0, 1.0,		b, b,
		0.0, 1.0, 1.0,		a, b,
		0.0, 0.0, 1.0,		a, a,

		//BOTTOM
		0.0, 0.0, 0.0,		a, a,
		1.0, 0.0, 0.0,		b, a,
		1.0, 0.0, 1.0,		b, b,
		1.0, 0.0, 1.0,		b, b,
		0.0, 0.0, 1.0,		a, b,
		0.0, 0.0, 0.0,		a, a,

		//TOP
		0.0, 1.0, 0.0,		a,   a,
		1.0, 1.0, 0.0,		b, a,
		1.0, 1.0, 1.0,		b, b,
		1.0, 1.0, 1.0,		b, b,
		0.0, 1.0, 1.0,		a,   b,
		0.0, 1.0, 0.0,		a,   a,

		//LEFT
		0.0, 0.0, 0.0,		a,   a,
		0.0, 0.0, 1.0,		b, a,
		0.0, 1.0, 1.0,		b, b,
		0.0, 1.0, 1.0,		b, b,
		0.0, 1.0, 0.0,		a,   b,
		0.0, 0.0, 0.0,		a,   a,

		//RIGHT
		1.0, 0.0, 0.0,		a,   a,
		1.0, 0.0, 1.0,		b, a,
		1.0, 1.0, 1.0,		b, b,
		1.0, 1.0, 1.0,		b, b,
		1.0, 1.0, 0.0,		a,   b,
		1.0, 0.0, 0.0,		a,   a,

	};

	buffer_vertex_array buffer_;
	GLfloat size_ = 0.4;
	std::vector<GLfloat> coords_;
	glm::vec3 spawnPosition_ = { 0.0f, 0.0f, 0.0f };


	void update_coords()
	{
		coords_.clear();
		int j = 0;
		for (auto i = shape_.begin() ;  i < shape_.end(); ++i,++j)
		{
			const auto k = j % 5;
			if (k <= 2)
			{
				coords_.push_back(size_ * (*i) + spawnPosition_[k]);
			}
			else 
			{
				coords_.push_back(*i);
			}
		
		}
	}



public:


	void bind_buffer()
	{

		update_coords();
		buffer_.bind_buffer(this->get_coords()->size() * sizeof GLuint, this->get_coords()->data());
	}
	void unbind_buffer()
	{
		buffer_.unbind();
	}
	void draw()
	{
		buffer_.draw(this->get_coords()->size());
	}
	std::vector<GLfloat>* get_coords()
	{
		return &coords_;
	}
	void set_spawn_position(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		spawnPosition_.x = x;
		spawnPosition_.y = y;
		spawnPosition_.z = z;
	}
	void set_size_rec(const GLfloat size)
	{
		size_ = size;
	}
	glm::vec3 get_spawn_position() const
	{
		return spawnPosition_;
	}
	block();
	~block();
};

