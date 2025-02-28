#pragma once
#include <unordered_map>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>


enum class Color
{
	TRANSPARENT,
	RED,
	GREEN,
	BLUE,
	WHITE,
	GOLD,
	BLACK,
	AMBER,
	BUTTER_SCOTCH
};


//	1 is full in the color channel. normalize the value between 0 and 1

static std::unordered_map<Color, glm::vec3> colorMap =
{
	{Color::TRANSPARENT,	glm::vec3(0.0f,		0.0f,	0.0f)},
	{Color::RED,			glm::vec3(1.0f,		0.0f,	0.0f)},
	{Color::GREEN,			glm::vec3(0.0f,		1.0f,	0.0f)},
	{Color::BLUE,			glm::vec3(0.0f,		0.0f,	1.0f)},
	{Color::WHITE,			glm::vec3(1.0f,		1.0f,	1.0f)},
	{Color::GOLD,			glm::vec3(1.0f,		0.843f, 0.0f)},
	{Color::BLACK,			glm::vec3(0.0f,		0.0f,	0.0f)},
	{Color::AMBER,			glm::vec3(1.0f,		0.749f,	0.0f)},
	{Color::BUTTER_SCOTCH,	glm::vec3(0.89f,	0.588f, 0.243f)},
};