#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/ShaderClass.h"
#include "Texture/Texture.h"
#include "Buffers/VAO.h"
#include "Buffers/EBO.h"
#include <unordered_map>
#include "Colors.h"
#include "TextData.h"

class TextRenderer
{
public:
	TextRenderer(Shader* shader, float screenWidth, float screenHeight);
	TextRenderer();
	~TextRenderer();

	void setScreenSize(float screenWidth, float screenHeight)
	{
		m_width = screenWidth;
		m_height = screenHeight;
	};

	void renderText(std::string, float x, float y, unsigned int fontSize, Alignment alignment, Color color, int textWrapPixels = -1, float textWrapOffset = 0.0f);

	float getFontSize(std::string text, float widthPercent, float heightPercent);

	float getTextLength(std::string text, unsigned int fontSize);
private:
	Shader* m_shader = nullptr;

	float m_width = 0.0f;
	float m_height = 0.0f;
	float m_atlasSquareSize = 0.1f;

	void displayText(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color color);
	void renderQuads(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color color);

	void buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int characterCount, unsigned int maxVertices, std::string text, float alignment);
	void buildIndices(GLuint* indices, unsigned int characterCount);
	void addSpace(GLfloat* vertices, float xPos, float yPos, unsigned int fontSize, int i);
	float findAlignment(Alignment alignment, std::string text, unsigned int fontSize);

private:

	std::vector<std::string> getWrappedText(std::string text, unsigned int fontSize, int textWrapPixels);

	void buildCharacter(GLfloat* vertices, int i, float* xPos, float yPos, unsigned int fontSize, float leftShift, float rightShift, glm::vec2 bottomLeftAtlas);

	std::vector<std::string> breakText(std::string text, unsigned int maxCharacters);
private:

	std::unordered_map<Color, Texture*> m_characterAtlas = { 
		{Color::WHITE , nullptr},
		{Color::BLACK , nullptr} 
	};

	float m_fontMapHSpacing = 0.0f;

	std::unordered_map<char, TextPosition> m_fontMap = {
	{'1', {0.0f,  9.0f, (6.0f / 10.0f), 0.0f}},
	{'2', {1.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'3', {2.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'4', {3.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'5', {4.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'6', {5.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'7', {6.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'8', {7.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'9', {8.0f,  9.0f, (5.0f / 10.0f), 0.0f}},
	{'0', {9.0f,  9.0f, (5.0f / 10.0f), 0.0f}},

	{'A', {0.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'B', {1.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'C', {2.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'D', {3.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'E', {4.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'F', {5.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'G', {6.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'H', {7.0f,  8.0f, (5.0f / 10.0f), 0.0f}},
	{'I', {8.0f,  8.0f, (6.0f / 10.0f), 0.0f}},
	{'J', {9.0f,  8.0f, (4.0f / 10.0f), 0.0f}},

	{'K', {0.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'L', {1.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'M', {2.0f,  7.0f, (4.0f / 10.0f), 0.0f}},
	{'N', {3.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'O', {4.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'P', {5.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'Q', {6.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'R', {7.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'S', {8.0f,  7.0f, (5.0f / 10.0f), 0.0f}},
	{'T', {9.0f,  7.0f, (4.0f / 10.0f), 0.0f}},

	{'U', {0.0f,  6.0f, (5.0f / 10.0f), 0.0f}},
	{'V', {1.0f,  6.0f, (4.0f / 10.0f), 0.0f}},
	{'W', {2.0f,  6.0f, (4.0f / 10.0f), 0.0f}},
	{'X', {3.0f,  6.0f, (5.0f / 10.0f), 0.0f}},
	{'Y', {4.0f,  6.0f, (4.0f / 10.0f), 0.0f}},
	{'Z', {5.0f,  6.0f, (5.0f / 10.0f), 0.0f}},
	{'a', {6.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'b', {7.0f,  6.0f, (4.0f / 10.0f), 0.0f}},
	{'c', {8.0f,  6.0f, (6.0f / 10.0f), 0.0f}},
	{'d', {9.0f,  6.0f, (4.0f / 10.0f), 0.0f}},

	{'e', {0.0f,  5.0f, (4.0f / 10.0f), 0.0f}},
	{'f', {1.0f,  5.0f, (6.0f / 10.0f), 0.0f}},
	{'g', {2.0f,  5.0f, (4.0f / 10.0f), 0.0f}},
	{'h', {3.0f,  5.0f, (5.0f / 10.0f), 0.0f}},
	{'i', {4.0f,  5.0f, (8.0f / 10.0f), 0.0f}},
	{'j', {5.0f,  5.0f, (6.0f / 10.0f), 0.0f}},
	{'k', {6.0f,  5.0f, (6.0f / 10.0f), 0.0f}},
	{'l', {7.0f,  5.0f, (8.0f / 10.0f), 0.0f}},
	{'m', {8.0f,  5.0f, (4.0f / 10.0f), 0.0f}},
	{'n', {9.0f,  5.0f, (6.0f / 10.0f), 0.0f}},

	{'o', {0.0f,  4.0f, (5.0f / 10.0f), 0.0f}},
	{'p', {1.0f,  4.0f, (5.0f / 10.0f), 0.0f}},
	{'q', {2.0f,  4.0f, (5.0f / 10.0f), 0.0f}},
	{'r', {3.0f,  4.0f, (5.0f / 10.0f), 0.0f}},
	{'s', {4.0f,  4.0f, (6.0f / 10.0f), 0.0f}},
	{'t', {5.0f,  4.0f, (6.0f / 10.0f), 0.0f}},
	{'u', {6.0f,  4.0f, (4.0f / 10.0f), 0.0f}},
	{'v', {7.0f,  4.0f, (4.0f / 10.0f), 0.0f}},
	{'w', {8.0f,  4.0f, (4.0f / 10.0f), 0.0f}},
	{'x', {9.0f,  4.0f, (6.0f / 10.0f), 0.0f}},

	{'y', {0.0f,  3.0f, (5.0f / 10.0f), 0.0f}},
	{'z', {1.0f,  3.0f, (5.0f / 10.0f), 0.0f}},
	{':', {2.0f,  3.0f, (6.0f / 10.0f), 0.0f}},
	{'\'',{3.0f,  3.0f, (6.0f / 10.0f), 0.0f}},
	{'#', {4.0f,  3.0f, (4.0f / 10.0f), 0.0f}},
	{'!', {5.0f,  3.0f, (8.0f / 10.0f), 0.0f}},
	{'^', {6.0f,  3.0f, (5.0f / 10.0f), 0.0f}},
	{',', {7.0f,  3.0f, (7.0f / 10.0f), 0.0f}},
	{'.', {8.0f,  3.0f, (8.0f / 10.0f), 0.0f}},
	{'?', {9.0f,  3.0f, (5.0f / 10.0f), 0.0f}},

	{'%', {0.0f,  2.0f, (4.0f / 10.0f), 0.0f}},
	{'(', {1.0f,  2.0f, (7.0f / 10.0f), 0.0f}},
	{')', {2.0f,  2.0f, (7.0f / 10.0f), 0.0f}},
	{'+', {3.0f,  2.0f, (6.0f / 10.0f), 0.0f}},
	{'_', {4.0f,  2.0f, (5.0f / 10.0f), 0.0f}},
	{'=', {5.0f,  2.0f, (6.0f / 10.0f), 0.0f}},
	{'{', {6.0f,  2.0f, (6.0f / 10.0f), 0.0f}},
	{'}', {7.0f,  2.0f, (6.0f / 10.0f), 0.0f}},
	{'/', {8.0f,  2.0f, (5.0f / 10.0f), 0.0f}},
	{'\\',{9.0f,  2.0f, (5.0f / 10.0f), 0.0f}},

	{'<',{0.0f,  1.0f, (7.0f / 10.0f), 0.0f}},
	{'>',{1.0f,  1.0f, (7.0f / 10.0f), 0.0f}},
	{';',{2.0f,  1.0f, (7.0f / 10.0f), 0.0f}},
	{'*',{3.0f,  1.0f, (7.0f / 10.0f), 0.0f}},
	{'~',{4.0f,  1.0f, (5.0f / 10.0f), 0.0f}},
	{'-',{5.0f,  1.0f, (6.0f / 10.0f), 0.0f}},
	};

};