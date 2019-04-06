#pragma once
#include "buffer_vertex_array.h"
#include <glm/detail/type_vec3.hpp>
#include <vector>



class rectangle
{
	GLfloat sizeRec_ = 0.4;
	std::vector<GLfloat> shape_ = 
	{
		0.0,  0.0,  0.0,  
		1.0,  0.0,  0.0,
		1.0,  1.0,  0.0,
		1.0,  1.0,  0.0,
		0.0,  1.0,  0.0, 
		0.0,  0.0,  0.0,
	};

	std::vector<GLfloat> coords_;
	glm::vec3 spawnPosition_ = { 0.0f, 0.0f, 0.0f};
	buffer_vertex_array buffer_;

	void update_coords()
	{
		coords_.clear();
		int j = 0;
		for (auto i = shape_.begin(); i < shape_.end(); ++i)
		{
			coords_.push_back(sizeRec_ * (*i) - sizeRec_ / 2 + spawnPosition_[j++ % 3]);
		}
	}

	
public:

	void bind_buffer()
	{
		
		update_coords();
		buffer_.bind_buffer(this->get_coords()->size() * sizeof GLfloat, this->get_coords()->data());
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
		sizeRec_ = size;
	}
	glm::vec3 get_spawn_position() const 
	{
		return spawnPosition_;
	}



	rectangle();
	~rectangle();
};

