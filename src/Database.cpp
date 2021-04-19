#include "pch.h"
#include "Database.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

void Database::LoadModel(const std::string& path)
{
	model_loader importer;
	scene scene = importer.read_file(path.c_str());

	_directory = path.substr(0, path.find_last_of('//'));
	std::cout << " directory: " << _directory << std::endl;

	ProcessNode(scene);
}

void Database::ProcessNode(const scene& scene)
{

	/*for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}*/

	/*for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}*/
	
	_data.push_back(ProcessMesh(scene));
}

Mesh Database::ProcessMesh(const scene& scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Texture* textures;

	for (unsigned int i = 0; i < scene.meshes.vertices.size(); i++)
	{
		Vertex vertex;


		glm::vec3 vector;
		vector.x = scene.meshes.vertices.at(i).x;
		vector.y = scene.meshes.vertices.at(i).y;
		vector.z = scene.meshes.vertices.at(i).z;
		vertex.Position = vector;

		vector.x = scene.meshes.normals.at(i).x;
		vector.y = scene.meshes.normals.at(i).y;
		vector.z = scene.meshes.normals.at(i).z;
		vertex.Normal = vector;

		glm::vec2 vec;
		vec.x = scene.meshes.textureCords.at(i).x;
		vec.y = scene.meshes.textureCords.at(i).y;
		vertex.TexCoords = vec;

		vertices.push_back(vertex);
	}

	/*	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}*/

	indices.reserve(scene.meshes.textureCords.size());
    for (auto i = 0; i < scene.meshes.textureCords.size(); ++i)
		indices.push_back(i);

	Texture texture;
	std::string path = "textureMap.png";
	texture.id = TextureFromFile(path.c_str(), _directory);
	texture.type = "test";
	texture.path = path.c_str();
	_texturesLoaded = texture;
	textures  = &_texturesLoaded;

	return Mesh(vertices, indices, textures);
}

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		std::cout << "directory: " << directory << std::endl;
		std::cout << "filename: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

Database::Database(const char* path)
{
	LoadModel(path);
}

std::vector<Vertex> Database::GetVertices() const {
    return _data.begin()->GetVertices();
}
