#pragma once
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* textures);
	Mesh() = default;
	void Draw(Shader* shader);
	void setupMesh();
	void Setup();
	void ClearData();
    void clear_data();
    void AddVertices(const Vertex& vertex);
    void AddIndices(unsigned int indice);
    void ClearVertices();
    void ClearIndices();
    void setTexture(Texture* texturePtr);

     std::vector<Vertex> GetVertices() const {return _vertices;}
     std::vector<unsigned int> GetIndices() const {return _indices;}
     Texture* GetTexture() const {return _texture;}
private:
    bool _setupFlag = false;
    bool _clearDataFlag = false;
	unsigned int VAO{};
    unsigned int VBO{};
    unsigned int EBO{};
    Texture* _texture{};
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
};