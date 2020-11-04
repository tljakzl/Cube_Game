#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class Shader
{
public:


	GLuint Program;
	Shader(const GLchar*, const GLchar*);
	void Use();
	void setInt(const std::string &name, int value) const;
	void setM4fv(const std::string & name, glm::mat4 value) const;
	void setFloat(const std::string& name, float value) const;
	void set_vec2(const std::string &name,glm::vec2 vec);
};

#endif

