#pragma once
#include "Mesh.h"
#include "model_loader.h"

class Database
{
public:
    explicit Database(const char* path);
    ~Database() = default;
    std::vector<Vertex> GetVertices() const;
    Texture* GetTexture() { return &_texturesLoaded; }
    const std::vector<Mesh>& data() { return _data;  }

private:
    void LoadModel(const std::string&  path);
    void ProcessNode(const scene& scene);
    Mesh ProcessMesh(const scene& scene);

private:
	Texture _texturesLoaded;
	std::string _directory;
	std::vector<Mesh> _data;


};

