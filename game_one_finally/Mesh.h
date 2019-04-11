#pragma once
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};


class Mesh {
public:
	//void set_texture(Shader shader);
	void clear_data();
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	Texture* textures;
	/*  Functions  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture* textures);
	Mesh() {}
	void Draw(Shader* shader);
	void setupMesh();
private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	
};