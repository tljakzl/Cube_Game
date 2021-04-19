#include "pch.h"
#include "Text.h"
#include <iostream>
#include <vector>

Text::Text()
{
	Load();
}

void Text::Load() {

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // find path to font
    std::string font_name = "fonts/15554.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return ;
    }

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set

    std::vector<uint8_t> textureNew;
    int textureSize = 512;
    textureNew.resize(textureSize * textureSize, 0);
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    unsigned int offsetX = 0;
    unsigned int offsetY = 0;
    unsigned int stepX = 42;
    unsigned int stepY = stepX * 1.1;
    for (auto c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        auto bitmap = face->glyph->bitmap;
        const auto numGrays = static_cast<float>(bitmap.num_grays);
        auto buffer = face->glyph->bitmap.buffer;

        // Если текущий символ по ширине слишком большой то переносим на следующиую строку
        if (offsetX + bitmap.width > textureSize) {
            offsetX = 0;
            offsetY += stepY;
        }

        for (auto y = 0; y < bitmap.rows; ++y) {
            auto* dataBuffer = buffer;
            for (auto x = 0; x < bitmap.width; ++x) {
                auto value = static_cast<unsigned int>(255.0f * (static_cast<float>(*dataBuffer++) / numGrays));
                // auto r  = (value & 0xf) *17;
                // auto g  = (value >> 4 & 0xf) *17;
                // auto b  = value;
                textureNew[(y + offsetY) * textureSize + (x + offsetX)] = value;
            }
            buffer += bitmap.pitch;
        }

        auto textSise = static_cast<float>(textureSize);
        auto xTexturePos = static_cast<float>(offsetX) / textSise;
        auto yTexturePos = static_cast<float>(offsetY) / textSise;
        auto heightInTexture = static_cast<float>(face->glyph->bitmap.rows) / textSise;
        auto widthInTexture = static_cast<float>(face->glyph->bitmap.width) / textSise;

        // now store character for later use
        Character character = {
                texture,
                static_cast<unsigned int>(face->glyph->advance.x),
                xTexturePos,
                yTexturePos,
                heightInTexture,
                widthInTexture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)
        };
        _characters.insert(std::pair<char, Character>(c, character));

        offsetX += bitmap.width + 1;
        if (offsetX >= textureSize) {
            offsetX = 0;
            offsetY += stepY;
        }
    }

    // TODO Исправить GL_RED на GL_ALPHA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textureSize, textureSize, 0, GL_RED, GL_UNSIGNED_BYTE, textureNew.data());
    std::cout << glGetError() << std::endl;

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);


// destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    BindBuffer();
}

void Text::BindBuffer()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



void Text::RenderText(Shader& shader, const std::string& text, float x, float y, float scale, const glm::vec3& color,const glm::mat4& projection)
{
    // activate corresponding render state
    shader.Use();
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);

    float offsetY = 0.f;
    float offsetSizeY = 30; // TODO Тут указываем размер переноса строки, нужно сделать универсально
    float xCurrent = x;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        if(*c == '\n'){
            offsetY -= offsetSizeY;
            xCurrent = x;
            continue;
        }

        Character ch = _characters[*c];

        float xpos = xCurrent + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale + offsetY;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   ch.xTexturePos, ch.yTexturePos },
                { xpos,     ypos,       ch.xTexturePos, ch.yTexturePos + ch.heightInTexture },
                { xpos + w, ypos,       ch.xTexturePos + ch.widthInTexture, ch.yTexturePos + ch.heightInTexture },

                { xpos,     ypos + h,   ch.xTexturePos, ch.yTexturePos },
                { xpos + w, ypos,       ch.xTexturePos + ch.widthInTexture, ch.yTexturePos + ch.heightInTexture },
                { xpos + w, ypos + h,   ch.xTexturePos + ch.widthInTexture, ch.yTexturePos }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        xCurrent += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::TestAtlas(Shader& shader, unsigned int textureID) {
    shader.Use();
    glm::vec3 color(1.0, 1.f, 1.0f);
    glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);
    static float vertices[6][4] = {
            {0.0f,   200.0f,   0.0f, 0.0f},
            {0.0f,   0.0f, 0.0f, 1.0f},
            {200.0f, 0.0f, 1.0f, 1.0f},

            {0.0f,   200.0f,   0.0f, 0.0f},
            {200.0f, 0.0f, 1.0f, 1.0f},
            {200.0f, 200.0f,   1.0f, 0.0f}
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, textureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    //x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

const Character& Text::GetCharacter(char character) {
    return _characters[character];
}
