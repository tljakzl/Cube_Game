#include "pch.h"
#include "Database.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

void Database::loadModel(std::string path)
{
	model_loader importer;
	scene scene = importer.read_file(path.c_str());

	directory = path.substr(0, path.find_last_of('//'));
	std::cout << " directory: " << directory << std::endl;

	processNode(scene);
}




void Database::processNode(const scene& scene)
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
	
	data.push_back(processMesh(scene));
}

Mesh Database::processMesh(const scene& scene)
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


		//if (mesh->mTextureCoords[0]) 
		//{

		//}
		/*else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);*/

		vertices.push_back(vertex);
	}

	/*	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}*/

	for (auto i = 0; i < scene.meshes.textureCords.size(); ++i)
		indices.push_back(i);




	/*if (mesh->mMaterialIndex >= 0)
	{
		material material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, textureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		/*std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}*/

	Texture texture;
	std::string path = "textureMap.png";
	texture.id = TextureFromFile(path.c_str(), directory);
	texture.type = "test";
	texture.path = path.c_str();
	textures_loaded = texture;
	textures  = &textures_loaded;

	return Mesh(vertices, indices, textures);
}

/*vector<Texture> Model::loadMaterialTextures(material& mat, textureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat.GetTextureCount(type); i++)
	{
		std::string str;
		mat.GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (strcmp(textures_loaded[j].path.data(), str.c_str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.c_str(), directory);
			texture.type = typeName;
			texture.path = str.c_str();
			textures.push_back(texture);

			textures_loaded.push_back(texture);
		}
	}
	return textures;
}*/



unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
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
	loadModel(path);
}


Database::~Database()
{
}

std::vector<Vertex> Database::GetVertices() const {
    return data.begin()->vertices;
}
