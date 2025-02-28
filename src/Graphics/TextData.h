#pragma once

enum class Alignment
{
	LEFT_ALIGN,
	CENTER_ALIGN,
	RIGHT_ALIGN
};

struct TextPosition
{
	float xCoord;
	float yCoord;
	float horizontalPadding;
	float verticalPadding;
};