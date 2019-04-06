#pragma once
#include <vector>
#include <glm/detail/type_vec3.hpp>

/*using pointer = const value_type*;
using reference = const value_type&;

// определите const_iterator
struct const_iterator : std::iterator<std::bidirectional_iterator_tag, value_type, long, pointer, reference>
{
	const ListT* ptr_;
	const_iterator(const ListT* v) :ptr_(v)
	{

	}

	const_iterator() = default;
	const_iterator(const const_iterator& iterator) = default;
	~const_iterator() = default;

	const_iterator operator++ (int)
	{
		const_iterator old(*this);
		this->operator++();
		return old;
	}

	const_iterator& operator++ ()
	{
		if (l_i != --ptr_->end())
		{
			if (v_i != --this->l_i->end())
				v_i.operator++();
			else {
				this->l_i.operator++();
				v_i = this->l_i->begin();
			}
		}
		else
		{
			if (v_i != this->l_i->end())
				v_i.operator++();
		}
		return *this;
	}


	const_iterator operator-- (int)
	{
		const_iterator old(*this);
		this->operator--();
		return old;
	}

	const_iterator& operator--()
	{

		if (v_i != this->l_i->begin())
			v_i.operator--();
		else {
			if (l_i != ptr_->begin())
			{
				this->l_i.operator--();
				v_i = this->l_i->end();
				v_i.operator--();
			}
		}
		return *this;
	}

	bool operator!= (const const_iterator& it) const
	{
		if (this->ptr_ == it.ptr_)
			if (this->l_i == it.l_i)
				if (this->v_i == it.v_i)
					return false;
		return true;
	}


	bool operator== (const const_iterator& it) const
	{
		if (this->ptr_ == it.ptr_)
			if (this->l_i == it.l_i)
				if (this->v_i == it.v_i)
					return true;
		return false;
	}


	pointer operator->() const
	{
		return &*v_i;
	}
	reference operator*() const
	{

		return *v_i;
	}

	typename ListT::const_iterator l_i;
	typename VectT::const_iterator v_i;
};

// определите методы begin / end
const_iterator begin() const
{
	if (data_.empty())
	{
		const_iterator temp;
		return temp;
	}

	const_iterator temp(&data_);
	temp.l_i = temp.ptr_->begin();
	temp.v_i = temp.l_i->begin();
	return  temp;
}
const_iterator end() const
{
	if (data_.empty())
	{
		const_iterator temp;
		return temp;
	}

	const_iterator temp(&data_);
	temp.l_i = (temp.ptr_->end()).operator--();
	temp.v_i = temp.l_i->end();
	return  temp;
}

// определите const_reverse_iterator
using const_reverse_iterator = std::reverse_iterator<const_iterator>;
// определите методы rbegin / rend
const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
const_reverse_iterator rend()   const { return const_reverse_iterator(begin()); }


*/





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


class ChunkRender
{

	using value_type = blockInfo;
	using pointer = const value_type*;
	using reference = const value_type&;

	using vec_x = std::vector<blockInfo>;
	using vec_z = std::vector<vec_x>;
	using vec_y = std::vector<vec_z>;
	struct block_psevdo_iterator
	{

		typedef vec_x::const_iterator vec_x_i;
		typedef vec_y::const_iterator vec_y_i;
		typedef vec_z::const_iterator vec_z_i;

		value_type* ptr_;

		vec_y* data;
		vec_x_i x_i;
		vec_y_i y_i;
		vec_z_i z_i;

		block_psevdo_iterator(vec_x_i x, vec_y_i y, vec_z_i z, vec_y* data_) :ptr_(x._Ptr), x_i(x), y_i(y), z_i(z), data(data_) {}

		~block_psevdo_iterator() = default;

		bool iter_up_x()
		{
			if (x_i + 1 != z_i->end())
			{
				++x_i;
				update_ptr();
				return true;
			}
			return false;
		}

		bool iter_down_x()
		{
			if (x_i != z_i->begin())
			{
				--x_i;
				update_ptr();
				return true;
			}
			return false;
		}

		bool iter_up_z()
		{
			if (z_i + 1 != y_i->end())
			{
				++z_i;
				update_z();
				return true;
			}
			return false;
		}

		bool iter_down_z()
		{
			if (z_i != y_i->begin())
			{
				--z_i;
				update_z();
				return true;
			}
			return false;
		}

		bool iter_up_y()
		{
			if (y_i + 1 != data->end())
			{
				++y_i;
				update_y();
				return true;
			}
			return false;
		}

		bool iter_down_y()
		{
			if (y_i != data->begin())
			{
				--y_i;
				update_y();
				return true;
			}
			return false;
		}

		void update_ptr() { ptr_ = x_i._Ptr; }
		void update_z() { x_i = z_i->begin() + x_i->position_.x; update_ptr(); }
		void update_y() { z_i = y_i->begin() + x_i->position_.z; update_z(); }



	};

	void set_block(blockInfo*, blockSide, glm::vec3, bool);
	void set_indices();
	void set_indices_x(blockInfo*, blockInfo*);
	void set_indices_y(blockInfo*, blockInfo*);
	void set_indices_z(blockInfo*, blockInfo*);
	void update_around_block(block_psevdo_iterator);
	void render();
	int size_x = 16;
	int size_y = 3;
	int size_z = 16;
public:

	

	


	blockInfo* get_block(int x, int y, int z);
	void iter_up_x(block_psevdo_iterator iterator);
	void iter_down_x(block_psevdo_iterator iterator);
	void iter_up_z(block_psevdo_iterator iterator);
	void iter_down_z(block_psevdo_iterator iterator);
	void iter_up_y(block_psevdo_iterator iterator);
	void iter_down_y(block_psevdo_iterator iterator);


	std::vector<std::vector<std::vector<blockInfo>>> chunk_data;

	ChunkRender();
	~ChunkRender();
};

