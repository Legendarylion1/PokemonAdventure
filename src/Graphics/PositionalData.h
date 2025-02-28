#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Graphics/Colors.h"
#include "../Graphics/TextData.h"
#include <string>

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum SpriteState
{
	STEP1,
	IDLE,
	STEP2
};

namespace renderOptions
{
	static const int autoSizeText = -1;
}

struct Coordinate
{
	//TODO: Possibly convert to unsigned int. Arugment against is for cutscenes were we want to bring a character in from nowhere
	int xTile = 0;
	int yTile = 0;

	float screenX = 0.0f;
	float screenY = 0.0f;

	bool operator==(const Coordinate other) const
	{
		if (this->xTile == other.xTile && this->yTile == other.yTile)
			return true;
		return false;
	}
};

class CoordinateHashFunction
{
public:
	size_t operator()(const Coordinate& coord) const
	{
		return (coord.xTile * 10000) + coord.yTile;			//If I ever make a map that is 10000 long in the y direction. Please get me help
	}
};

struct Position
{
	Coordinate coords;
	Direction direction;
	SpriteState spriteState = SpriteState::IDLE;
	float turnCount = 0.0f;

	bool operator==(const Position other) const
	{
		if (this->coords == other.coords && this->direction == other.direction)
			return true;
		return false;
	}

	bool operator!=(const Position other) const{ return !(*this == other); }
};

struct ButtonRenderData
{
	float percentageX = 50.0f;
	float percentageY = 50.0f;

	float widthPercent = 30.0f;
	float heightPercent = 20.0f;

	Color color = Color::RED;

	int fontSize = renderOptions::autoSizeText;

	bool* visible = nullptr;

	std::string image;

	bool highlight = true;
};

struct TextBoxRenderData
{
	float percentageX = 50.0f;
	float percentageY = 50.0f;

	float fontSizePercentage = 50.0f;

	Color color = Color::BLACK;
	Alignment alignment = Alignment::CENTER_ALIGN;

	float textWrapPercent = -1.0f;
	float textWrapOffsetPercent = 0.0f;
};

struct ImageRenderData
{
	float percentageX = 50.0f;
	float percentageY = 50.0f;

	float widthPercent = 20.0f;
	float heightPercent = 20.0f;

	std::string staticImage;
	std::string* dynamicImage = nullptr;

	bool* visible = nullptr;
	bool deleteWithScene = true;
};

struct ImageTextureCoords
{
	float bottomLeftX = 0.0f;
	float bottomLeftY = 0.0f;

	float bottomRightX = 1.0f;
	float bottomRightY = 0.0f;

	float topRightX = 1.0f;
	float topRightY = 1.0f;

	float topLeftX = 0.0f;
	float topLeftY = 1.0f;
};

struct DynamicImageRenderData
{
	float percentageX = 50.0f;
	float percentageY = 50.0f;

	float widthPercent = 20.0f;
	float heightPercent = 20.0f;

	std::string dynamicImage;

	glm::vec4 color = glm::vec4(0.0f);

	ImageTextureCoords imageTextureCoords{};

	float alpha = 0.0f;	//TODO: Redundant alpha reference
	bool deleteWithScene = true;
};

struct RectangleRenderData
{
	float bottomLeftXPercentage = 50.0f;
	float bottomLeftYPercentage = 50.0f;

	float heightPercent = 5.0f;			//TODO: Swap width and height lol
	float* widthPercent = nullptr;

	Color color = Color::GOLD;
	bool deleteWithScene = true;
};

struct PolygonData
{
	unsigned int indicesToDraw = 0;
	GLfloat verticeData[100]{};
	GLuint indiceData[100]{};

	bool visible = false;
	bool deleteWithScene = true;
};