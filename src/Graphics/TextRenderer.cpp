#include "TextRenderer.h"
#include "../GlobalData/helperFunctions.h"

TextRenderer::TextRenderer(Shader* shader, float screenWidth, float screenHeight) :
	m_shader(shader)
{
	m_characterAtlas[Color::WHITE] = new Texture("Images/Text/alphaNumerics.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterAtlas[Color::WHITE]->texUnit(*m_shader, "tex0", 0);

	m_characterAtlas[Color::BLACK] = new Texture("Images/Text/alphaNumericsBlack.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterAtlas[Color::BLACK]->texUnit(*m_shader, "tex0", 0);

	setScreenSize(screenWidth, screenHeight);
}

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
	//delete m_characterAtlas;
}

void TextRenderer::renderText(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color color, int textWrapPixels, float textWrapOffset)
{
	if (textWrapPixels == -1)
	{
		displayText(text, x, y, fontSize, alignment, color);
		return;
	}
	
	if (getTextLength(text, fontSize) <= textWrapPixels)
	{
		displayText(text, x, y, fontSize, alignment, color);
		return;
	}

	
	std::vector<std::string> wrappedText = getWrappedText(text, fontSize, textWrapPixels);
	for (int i = 0; i < wrappedText.size(); i++)
	{
		float decrease = (fontSize * i) + (textWrapOffset * i);
		displayText(wrappedText.at(i), x, y - decrease, fontSize, alignment, color);
	}
}

float TextRenderer::getFontSize(std::string text, float widthPercent, float heightPercent)
{
	float textHeight = m_height * (heightPercent / 100.0f) * (3.0f / 4.0f);
	float textWidth = m_width * (widthPercent / 100.0f);

	float maxSize = textHeight;

	float fontSize = textWidth / text.size();

	for (int i = 1; i < text.size(); i++)
	{
		if (text.at(i) = ' ')
			continue;
		fontSize -= (fontSize * m_fontMap[text.at(i)].horizontalPadding);
	}

	if (fontSize < textHeight)
		return fontSize;
	else
		return textHeight;
}

void TextRenderer::displayText(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color color)
{
	// TODO: Handle our limit special Characters

	if (text.size() <= 100)
	{
		renderQuads(text, x, y, fontSize, alignment, color);
		return;
	}

	std::vector<std::string> spacedText = breakText(text, 100);

	float offset = 0.0f;

	for (std::string val : spacedText)
	{
		renderQuads(val, x + offset, y, fontSize, alignment, color);
		offset += getTextLength(val, fontSize);
	}

}

void TextRenderer::renderQuads(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color color)
{
	unsigned int characterCount = text.size();

	const unsigned int MAX_QUADS = 100;
	const unsigned int MAX_VERTICES = (MAX_QUADS * 36) + 35;
	const unsigned int MAX_INDICES = MAX_QUADS * 6;

	GLfloat vertices[MAX_VERTICES]{};
	GLuint indices[MAX_INDICES]{};

	Color bindColor = Color::WHITE;
	if (color == Color::BLACK)
		bindColor = Color::BLACK;

	buildIndices(indices, MAX_INDICES);
	buildVertices(vertices, x, y, fontSize, characterCount, MAX_VERTICES, text, findAlignment(alignment, text, fontSize));

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	m_characterAtlas[bindColor]->Bind();
	VAO1.Bind();

	glm::mat4 proj = glm::ortho(0.0f, m_width, 0.0f, m_height, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj));

	glDrawElements(GL_TRIANGLES, 6 * characterCount, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();
	m_characterAtlas[bindColor]->Unbind();

	EBO1.Delete();
	VBO1.Delete();
	VAO1.Delete();
}

float TextRenderer::getTextLength(std::string text, unsigned int fontSize)
{
	float length = 0.0f;

	for (int i = 0; i < text.size(); i++)
	{
		if (text.at(i) == ' ')
		{
			length += (fontSize / 2.0f);
			continue;
		}

		length += fontSize - (m_fontMap[text.at(i)].horizontalPadding * fontSize);

	}
	
	return length;
}

void TextRenderer::buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int characterCount, unsigned int maxVertices, std::string text, float alignment)
{
	// Font size is the width and height of the quad
	// If Odd character Count we center Around the middle value
	// If Even character Count we center around the middle of the spacing between the characters


	// Step 1. Find the far left
	// Step 2. Build up the vertices
	// Step 2.5		Find the positions of the characters in the atlas
	// Step 3  Return

	// Step 1
	float xPos = x + alignment;
	float yPos = y;


	// Step 2

	for (int i = 0; i < characterCount; i++)
	{
		glm::vec2 bottomLeftAtlas;

		//Step 2.5
		if (text.at(i) == ' ')
		{
			addSpace(vertices, xPos, yPos, fontSize, i);
			xPos += (fontSize / 2.0f);
			continue;
		}
		bottomLeftAtlas = glm::vec2(m_fontMap[text.at(i)].xCoord * m_atlasSquareSize, m_fontMap[text.at(i)].yCoord * m_atlasSquareSize);

		//quadBufferPtr->Position = { xPos, yPos, LAYER_FIVE };
		//quadBufferPtr->Color = { 0.0f,0.0f,0.0f };
		//quadBufferPtr->TexCoords = {bottomLeftAtlas.x,bottomLeftAtlas.y};
		//quadBufferPtr++;

		buildCharacter(vertices, i, &xPos, yPos, fontSize, (m_fontMap[text.at(i)].horizontalPadding * fontSize), 0, bottomLeftAtlas);

	}

	// Step 3 :)
}

void TextRenderer::buildIndices(GLuint* indices, unsigned int characterCount)
{
	//0, 2, 1,
	//0, 3, 2,

	unsigned int offset = 0;
	for (int i = 0; i < characterCount; i += 6)
	{
		indices[i + 0] = offset;
		indices[i + 1] = offset + 2;
		indices[i + 2] = offset + 1;
		indices[i + 3] = offset;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 2;

		offset += 4;
	}
}

void TextRenderer::addSpace(GLfloat* vertices, float xPos, float yPos, unsigned int fontSize, int i)
{
	glm::vec2 bottomLeftAtlas = glm::vec2(0.001f, 0.001f);


	// Bottom Left
	vertices[36 * i] = xPos;
	vertices[(36 * i) + 1] = yPos;
	vertices[(36 * i) + 2] = 0.0f;
	vertices[(36 * i) + 3] = 0.0f;
	vertices[(36 * i) + 4] = 0.0f;
	vertices[(36 * i) + 5] = 0.0f;
	vertices[(36 * i) + 6] = 0.0f;
	vertices[(36 * i) + 7] = bottomLeftAtlas.x;
	vertices[(36 * i) + 8] = bottomLeftAtlas.y;

	// Top Left
	vertices[(36 * i) + 9] = xPos;
	vertices[(36 * i) + 10] = yPos + (fontSize / 2.0f);
	vertices[(36 * i) + 11] = 0.0f;
	vertices[(36 * i) + 12] = 0.0f;
	vertices[(36 * i) + 13] = 0.0f;
	vertices[(36 * i) + 14] = 0.0f;
	vertices[(36 * i) + 15] = 0.0f;
	vertices[(36 * i) + 16] = bottomLeftAtlas.x;
	vertices[(36 * i) + 17] = bottomLeftAtlas.y;

	// Top Right
	vertices[(36 * i) + 18] = xPos + (fontSize / 2.0f);
	vertices[(36 * i) + 19] = yPos + (fontSize / 2.0f);
	vertices[(36 * i) + 20] = 0.0f;
	vertices[(36 * i) + 21] = 0.0f;
	vertices[(36 * i) + 22] = 0.0f;
	vertices[(36 * i) + 23] = 0.0f;
	vertices[(36 * i) + 24] = 0.0f;
	vertices[(36 * i) + 25] = bottomLeftAtlas.x;
	vertices[(36 * i) + 26] = bottomLeftAtlas.y;

	// Bottom Right
	vertices[(36 * i) + 27] = xPos + (fontSize / 2.0f);
	vertices[(36 * i) + 28] = yPos;
	vertices[(36 * i) + 29] = 0.0f;
	vertices[(36 * i) + 30] = 0.0f;
	vertices[(36 * i) + 31] = 0.0f;
	vertices[(36 * i) + 32] = 0.0f;
	vertices[(36 * i) + 33] = 0.0f;
	vertices[(36 * i) + 34] = bottomLeftAtlas.x;
	vertices[(36 * i) + 35] = bottomLeftAtlas.y;
}

float TextRenderer::findAlignment(Alignment alignment, std::string text, unsigned int fontSize)
{
	int count = 0;

	if (alignment == Alignment::LEFT_ALIGN)
	{
		return 0.0f;
	}
	else if (alignment == Alignment::CENTER_ALIGN)
	{

		float totalDistance = 0.0f;

		//for (char c : text)
		for (int i = 0; i < text.size(); i++)
		{
			if (text.at(i) == ' ')
			{
				totalDistance += (fontSize / 2.0f);
				continue;
			}

			totalDistance += fontSize - (fontSize * m_fontMap[text.at(i)].horizontalPadding);

			count++;
		}

		return -1 * (totalDistance / 2.0f);

	}
	else if (alignment == Alignment::RIGHT_ALIGN)
	{
		float totalDistance = 0.0f;

		for (char c : text)
		{
			if (c == ' ')
			{
				totalDistance += (fontSize / 2.0f);
				continue;
			}

			totalDistance += fontSize - (fontSize * m_fontMap[c].horizontalPadding);

			count++;
		}

		return -1 * totalDistance;
	}

	return 0.0f;
}

std::vector<std::string> TextRenderer::getWrappedText(std::string text, unsigned int fontSize, int textWrapPixels)
{
	std::vector<std::string> data;

	std::string current = "";

	std::vector<std::string> splitData = splitString(text, ' ');

	int count = 0;
	bool addSpace = true;

	while (count < splitData.size())
	{
		if (data.size() == splitData.size())
			return data;

		if (count + 1 >= splitData.size())
			addSpace = false;

		std::string proposedAddition = splitData.at(count);
		if (addSpace)
			proposedAddition += " ";

		addSpace = true;

		float textLength = getTextLength(current + proposedAddition, fontSize);

		if (textLength < textWrapPixels)
			current += proposedAddition;
		else if (textLength == textWrapPixels)
		{
			current += proposedAddition;
			data.push_back(current);
			current = "";
		}
		else
		{
			data.push_back(current);
			current = "";
			continue;
		}

		addSpace = true;

		count++;
	}

	if (current.size() > 0)
		data.push_back(current);

	return data;
}

void TextRenderer::buildCharacter(GLfloat* vertices, int i, float* xPos, float yPos, unsigned int fontSize, float leftShift, float rightShift, glm::vec2 bottomLeftAtlas)
{
	//TODO: Rename left shift

	// Bottom Left
	vertices[36 * i] = *xPos + rightShift;
	vertices[(36 * i) + 1] = yPos;
	vertices[(36 * i) + 2] = 0.0f;
	vertices[(36 * i) + 3] = 0.0f;
	vertices[(36 * i) + 4] = 0.0f;
	vertices[(36 * i) + 5] = 0.0f;
	vertices[(36 * i) + 6] = 0.0f;
	vertices[(36 * i) + 7] = bottomLeftAtlas.x;
	vertices[(36 * i) + 8] = bottomLeftAtlas.y;

	// Top Left
	vertices[(36 * i) + 9] = *xPos + rightShift;
	vertices[(36 * i) + 10] = yPos + fontSize;
	vertices[(36 * i) + 11] = 0.0f;
	vertices[(36 * i) + 12] = 0.0f;
	vertices[(36 * i) + 13] = 0.0f;
	vertices[(36 * i) + 14] = 0.0f;
	vertices[(36 * i) + 15] = 0.0f;
	vertices[(36 * i) + 16] = bottomLeftAtlas.x;
	vertices[(36 * i) + 17] = bottomLeftAtlas.y + m_atlasSquareSize;

	// Top Right
	vertices[(36 * i) + 18] = *xPos + fontSize + rightShift;
	vertices[(36 * i) + 19] = yPos + fontSize;
	vertices[(36 * i) + 20] = 0.0f;
	vertices[(36 * i) + 21] = 0.0f;
	vertices[(36 * i) + 22] = 0.0f;
	vertices[(36 * i) + 23] = 0.0f;
	vertices[(36 * i) + 24] = 0.0f;
	vertices[(36 * i) + 25] = bottomLeftAtlas.x + m_atlasSquareSize;
	vertices[(36 * i) + 26] = bottomLeftAtlas.y + m_atlasSquareSize;

	// Bottom Right
	vertices[(36 * i) + 27] = *xPos + fontSize + rightShift;
	vertices[(36 * i) + 28] = yPos;
	vertices[(36 * i) + 29] = 0.0f;
	vertices[(36 * i) + 30] = 0.0f;
	vertices[(36 * i) + 31] = 0.0f;
	vertices[(36 * i) + 32] = 0.0f;
	vertices[(36 * i) + 33] = 0.0f;
	vertices[(36 * i) + 34] = bottomLeftAtlas.x + m_atlasSquareSize;
	vertices[(36 * i) + 35] = bottomLeftAtlas.y;

	*xPos += fontSize - leftShift + rightShift;
}

std::vector<std::string> TextRenderer::breakText(std::string text, unsigned int maxCharacters)
{
	std::vector<std::string> data;

	std::string placeholder = "";

	for (int i = 0; i < text.size(); i++)
	{
		if (placeholder.size() == maxCharacters)
		{
			data.push_back(placeholder);
			placeholder = "";
		}

		placeholder += text.at(i);
	}

	if (placeholder.size() > 0)
		data.push_back(placeholder);

	return data;
}
