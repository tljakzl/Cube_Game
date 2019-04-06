#pragma once
#include "Mesh.h"
#include "model_loader.h"





class Database
{
	void loadModel(std::string path);
	void processNode(const scene& scene);
	Mesh processMesh(const scene& scene);


public:

	std::vector<Texture> textures_loaded;
	string directory;
	vector<Mesh> data;
	Database(const char* path);
	~Database();
};

