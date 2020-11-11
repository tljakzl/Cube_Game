#pragma once
#include "Mesh.h"
#include "model_loader.h"

class Database
{
	void loadModel(std::string path);
	void processNode(const scene& scene);
	Mesh processMesh(const scene& scene);

public:

	Texture textures_loaded;
	std::string directory;
	std::vector<Mesh> data;
	std::vector<Vertex> GetVertices() const;
	explicit Database(const char* path);
	~Database();
};

