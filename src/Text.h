#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "GL/glew.h"
#include <map>
#include "Shader.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID = 0; // ID handle of the glyph texture
    unsigned int Advance = 0;   // Horizontal offset to advance to next glyph
    float xTexturePos = .0f;
    float yTexturePos = .0f;
    float heightInTexture = .0f;
    float widthInTexture = .0f;
    glm::ivec2 Size;      // Size of glyph
    glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
};

class Text
{
public:
    Text();
    ~Text() = default;

	void RenderText(Shader& shader, const std::string& text, float x, float y, float scale, const glm::vec3& color, const glm::mat4& projection);
	void TestAtlas(Shader& shader, unsigned int textureID);
    const Character& GetCharacter(char character);

private:
    void Load();
    void BindBuffer();
private:

    unsigned int _vao;
    unsigned int _vbo;
    std::map<char, Character> _characters;
};

