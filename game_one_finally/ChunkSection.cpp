#include "pch.h"
#include "ChunkSection.h"
#include <random>
#include <glm/detail/func_exponential.inl>
#include <valarray>


blockInfo* ChunkSection::get_block(glm::vec3 pos_block)
{

	int x = static_cast<int>(abs(pos_block.x)) % 16;
	int z = static_cast<int>(abs(pos_block.z)) % 16;
	int y = static_cast<int>(abs(pos_block.y)) % 16;


	if (pos_block.x < 0)
		x = static_cast<int>(pos_block.x) % 16 + 15;
	
	if (pos_block.z < 0)
		z = static_cast<int>(pos_block.z) % 16 + 15;



	int key =  x + y * chunk_section_size_z*chunk_section_size_x +  z * chunk_section_size_z;
	auto *block = &chunk_section_data.at(key);
	return block;
}

ChunkSection::ChunkSection(glm::vec3 position)
{
	render(position);
}


ChunkSection::~ChunkSection()
{
}





static double Lerp(double a, double b, double t)
{
	// return a * (t - 1) + b * t; можно переписать с одним умножением (раскрыть скобки, взять в другие скобки):
	return a + (b - a) * t;
}

static double QunticCurve(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}






struct vec2
{
	vec2(double x, double y) :x_(x), y_(y) {}
	double x_;
	double y_;
};


double Dot(vec2 a, vec2 b)
{
	return a.x_*b.x_ + a.y_*b.y_;
}

std::vector<double> random_vectors;

vec2 make_vector(int x, int y)
{
	int v = (int)(((x * 1'836'311'903) ^ (y * 2'971'215'073) + 4'807'526'976) & 1023);

	v = random_vectors.at(v);
	auto x_ = cos(v);
	auto y_ = sin(v);
	return vec2(x_, y_);
}



void make_vectors(double seed)
{
	std::minstd_rand rnd;
	rnd.seed(seed);
	for (auto i = 0; i < 1024; i++)
		random_vectors.push_back(rnd());
}


double noize(double x, double y, double freq)
{
	
	int block_size = freq;


	int counter = 0;
	

	if (x >= 0)
		counter = 0;
	else counter = -1;
	int chunk_x = (int)((x + 0.5) / block_size) + counter;

	if (y >= 0)
		counter = 0;
	else counter = -1;
	int chunk_y = (int)((y + 0.5) / block_size) + counter;




	//int p_d_l_x = (x + 0.5) / block_size;
	//int p_d_l_y = (y + 0.5) / block_size;

	double local_x;


		local_x = x / block_size - chunk_x;
	
	double local_y =  y  / block_size - chunk_y;


	// вектора от вершин квадрата до точки внутри квадрата:
	vec2 distanceToTopLeft     = vec2(local_x , local_y);
	vec2 distanceToTopRight    = vec2(local_x - 1, local_y);
	vec2 distanceToBottomLeft  = vec2(local_x, local_y - 1);
	vec2 distanceToBottomRight = vec2(local_x - 1, local_y - 1);


	vec2 topLeftGradient     = make_vector(chunk_x , chunk_y);
	vec2 topRightGradient    = make_vector(chunk_x + 1, chunk_y);
	vec2 bottomLeftGradient  = make_vector(chunk_x , chunk_y+1);
	vec2 bottomRightGradient = make_vector(chunk_x + 1, chunk_y + 1);


	double tx1 = Dot(distanceToTopLeft, topLeftGradient);
	double tx2 = Dot(distanceToTopRight, topRightGradient);
	double bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
	double bx2 = Dot(distanceToBottomRight, bottomRightGradient);

	// готовим параметры интерполяции, чтобы она не была линейной:
	local_x = QunticCurve(local_x);
	local_y = QunticCurve(local_y);

	// собственно, интерполяция:
	double tx = Lerp(tx1, tx2, local_x);
	double bx = Lerp(bx1, bx2, local_x);
	double tb = Lerp(tx, bx, local_y);


	return (tb+ 1)/2;

}






void ChunkSection::render(glm::vec3 position)
{
	glm::vec3 pos = position;
	int delta_x = 0;
	int delta_z = 0;

	if(position.x < 0 && position.z < 0)
	{
		delta_x = 1;
		delta_z = 1;
	}

	if (position.x < 0 && position.z > 0)
	{
		pos.z -= chunk_section_size_z;
		delta_x = 1;
	}
	if (position.x > 0 && position.z < 0)
	{
		pos.x -= chunk_section_size_x;
		delta_z = 1;
	}
		
	if (position.x > 0 && position.z > 0)
	{
		pos.x -= chunk_section_size_x ;
		pos.z -= chunk_section_size_z ;

	}

	make_vectors(1723);

	for (auto y = 0; y < chunk_section_size_y; ++y)
	{
		for (auto z = 0; z < chunk_section_size_z; ++z)
		{
			for (auto x = 0; x < chunk_section_size_x; ++x)
			{

				int height = (int)(100* pow(noize((x + pos.x)*2 , (z + pos.z)*2 , 70),4)) + 1;

				if(y < height)
				{
					blockInfo block;
					block.position_ = glm::vec3(x, y, z) + pos;
					block.notempty = true;
					block.type_ = 1;
					chunk_section_data.push_back(block);
					
				}
				else
				{
					blockInfo block;
					block.position_ = glm::vec3(x, y, z) + pos;
					block.notempty = false;
					block.type_ = 1;
					chunk_section_data.push_back(block);
					
				}


			}
		}
	}
}





