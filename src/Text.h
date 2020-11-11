#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "GL/glew.h"
#include <map>
#include "Shader.h"

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class Text
{
	std::map<GLchar, Character> Characters;
	FT_Library ft;
	FT_Face face;

	GLuint VAO, VBO;

	void load();
	void bind_buffer();
public:
	void render_text(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	Text();
	~Text();
};

