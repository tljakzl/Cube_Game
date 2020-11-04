#pragma once


#include "Shader.h"
#include "Mesh.h"
#include "Database.h"

//#include "model_loader.h"
//#include <glm/detail/type_vec3.hpp>






class Model
{
public:

	

	Model(const Database database,glm::vec3 position = { 0.0f,0.0f,0.0f }):position_(position)
	{
		load_data(database);
	}
	Model(const Database database,  glm::vec3 position , std::vector<unsigned>* side) :position_(position)
	{
		load_data(database, side);
	}

	void set_position(const char* path, glm::vec3 position);
	void Draw(Shader* shader);
	void clear_data();
private:
	void load_data(Database database);
	void load_data(Database database,std::vector<unsigned>* sides);

	glm::vec3 position_;
	vector<Mesh> meshes;

	

	
};


