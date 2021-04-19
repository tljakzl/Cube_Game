#include "pch.h"
#include "Mesh.h"

#include <utility>




Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* textures)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
	_texture = textures;

	setupMesh();
}

void Mesh::Draw(Shader* shader) {
    /*unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}*/


    if (_clearDataFlag) {
        clear_data();
        _clearDataFlag = false;
    }

    if (_setupFlag) {
        setupMesh();
        _setupFlag = false;
    }

    glBindTexture(GL_TEXTURE_2D, _texture->id);
    glActiveTexture(GL_TEXTURE1);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setupMesh()
{
	if (_vertices.size() != 0)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

		glBindVertexArray(0);
	}
}


void Mesh::clear_data()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::ClearData() {
    _clearDataFlag = true;
}

void Mesh::Setup() {
    _setupFlag = true;
}

void Mesh::AddVertices(const Vertex &vertex) {
    _vertices.push_back(vertex);
}

void Mesh::AddIndices(unsigned int indice) {
    _indices.push_back(indice);
}

void Mesh::setTexture(Texture* texturePtr) {
    _texture = texturePtr;
}

void Mesh::ClearVertices() {
    _vertices.clear();
    _vertices.shrink_to_fit();
}

void Mesh::ClearIndices() {
    _indices.clear();
    _indices.shrink_to_fit();
}

