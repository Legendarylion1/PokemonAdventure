#pragma once
#include "../Menu.h"
#include "../../Map/MapHandler.h"
#include "MenuSetup.h"


namespace MenuFunction
{
	namespace
	{

		static float getScreenXPercent(float screenCoord, Resolution resolution)
		{
			return (screenCoord / resolution.x) * 100.0f;
		};

		static float getScreenYPercent(float screenCoord, Resolution resolution)
		{
			return (screenCoord / resolution.y) * 100.0f;
		};

		static std::string formatStringLength(std::string start, std::string end, int totalLength)
		{
			std::string padding = "";

			int sizeRemaining = totalLength - start.length() + end.length();

			for (int i = 0; i < sizeRemaining; i++)
			{
				padding += " ";
			}

			return start + padding + end;
		}

		static void updatePokemonSummaryGraph(SummaryData* data, Pokemon pokemon, Resolution resolution)
		{
			// Point Indice Values
			// Center:	0
			// Top:		1
			// Bottom:	2
			// Top R:	3
			// Bot R:	4
			// Top L:	5
			// Bot L:	6

			std::vector<GLuint> indices = 
			{
				0, 1, 3,
				0, 3, 4,

				0, 4, 2,
				0, 2, 6,

				0, 6, 5,
				0, 5, 1
			};

			float GraphSizePercent = 10.0f;
			float GraphBorderPercent = 1.0f;
			float StatGraphBaseSize = 3.0f;
			float xPercent = 50.0f;
			float yPercent = 35.0f;
			float fontDownSize = 5.0f;
			float fontGraphOffset = 1.0f;

			//TODO: Make this a global value
			int evMax = 260100;

			//TODO: Can Move so that we dont have to change the values every time
			for (int i = 0; i < indices.size(); i++)
			{
				data->evStatContainerOutline.indiceData[i] = indices.at(i);
				data->evStatContainer.indiceData[i] = indices.at(i);
				data->evStatGraph.indiceData[i] = indices.at(i);
			}

			data->evStatContainerOutline.visible = true;
			data->evStatContainer.visible = true;
			data->evStatGraph.visible = true;

			float triangleLineLength = resolution.y * (GraphSizePercent / 100.0f);
			float triangleHeight = triangleLineLength * (sqrt(3) / 2.0f);
			
			float xCenter = resolution.x * (xPercent / 100.0f);
			float yCenter = resolution.y * (yPercent / 100.0f);

			float innerTriangleLineLength = resolution.y * ((GraphSizePercent - GraphBorderPercent) / 100.0f);
			float innerTriangleHeight = innerTriangleLineLength * (sqrt(3) / 2.0f);

			// Outline Points
			{
				// Center				0
				{
					data->evStatContainerOutline.verticeData[0] = xCenter;
					data->evStatContainerOutline.verticeData[1] = yCenter;
					data->evStatContainerOutline.verticeData[2] = 0.0f;
					data->evStatContainerOutline.verticeData[3] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6] = 0.0f;
				}

				// Top Point			1
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 1)] = xCenter;
					data->evStatContainerOutline.verticeData[1 + (7 * 1)] = yCenter + triangleLineLength;
					data->evStatContainerOutline.verticeData[2 + (7 * 1)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 1)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 1)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 1)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 1)] = 0.0f;
				}

				// Bottom Point			2
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 2)] = xCenter;
					data->evStatContainerOutline.verticeData[1 + (7 * 2)] = yCenter - triangleLineLength;
					data->evStatContainerOutline.verticeData[2 + (7 * 2)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 2)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 2)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 2)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 2)] = 0.0f;
				}

				// Top Right Point		3
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 3)] = xCenter + triangleHeight;
					data->evStatContainerOutline.verticeData[1 + (7 * 3)] = yCenter + (triangleLineLength / 2.0f);
					data->evStatContainerOutline.verticeData[2 + (7 * 3)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 3)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 3)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 3)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 3)] = 0.0f;
				}

				// Bottom Right Point	4
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 4)] = xCenter + triangleHeight;
					data->evStatContainerOutline.verticeData[1 + (7 * 4)] = yCenter - (triangleLineLength / 2.0f);
					data->evStatContainerOutline.verticeData[2 + (7 * 4)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 4)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 4)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 4)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 4)] = 0.0f;
				}

				// Top Left Point		5
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 5)] = xCenter - triangleHeight;
					data->evStatContainerOutline.verticeData[1 + (7 * 5)] = yCenter + (triangleLineLength / 2.0f);
					data->evStatContainerOutline.verticeData[2 + (7 * 5)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 5)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 5)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 5)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 5)] = 0.0f;
				}

				// Bottom Left Point	6
				{
					data->evStatContainerOutline.verticeData[0 + (7 * 6)] = xCenter - triangleHeight;
					data->evStatContainerOutline.verticeData[1 + (7 * 6)] = yCenter - (triangleLineLength / 2.0f);
					data->evStatContainerOutline.verticeData[2 + (7 * 6)] = 0.0f;
					data->evStatContainerOutline.verticeData[3 + (7 * 6)] = colorMap[Color::RED].r;
					data->evStatContainerOutline.verticeData[4 + (7 * 6)] = colorMap[Color::RED].g;
					data->evStatContainerOutline.verticeData[5 + (7 * 6)] = colorMap[Color::RED].b;
					data->evStatContainerOutline.verticeData[6 + (7 * 6)] = 0.0f;
				}
			}

			// Inner Points
			{
				// Center				0
				{
					data->evStatContainer.verticeData[0] = xCenter;
					data->evStatContainer.verticeData[1] = yCenter;
					data->evStatContainer.verticeData[2] = 0.0f;
					data->evStatContainer.verticeData[3] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6] = 0.0f;
				}

				// Top Point			1
				{
					data->evStatContainer.verticeData[0 + (7 * 1)] = xCenter;
					data->evStatContainer.verticeData[1 + (7 * 1)] = yCenter + innerTriangleLineLength;
					data->evStatContainer.verticeData[2 + (7 * 1)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 1)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 1)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 1)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 1)] = 0.0f;
				}

				// Bottom Point			2
				{
					data->evStatContainer.verticeData[0 + (7 * 2)] = xCenter;
					data->evStatContainer.verticeData[1 + (7 * 2)] = yCenter - innerTriangleLineLength;
					data->evStatContainer.verticeData[2 + (7 * 2)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 2)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 2)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 2)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 2)] = 0.0f;
				}

				// Top Right Point		3
				{
					data->evStatContainer.verticeData[0 + (7 * 3)] = xCenter + innerTriangleHeight;
					data->evStatContainer.verticeData[1 + (7 * 3)] = yCenter + (innerTriangleLineLength / 2.0f);
					data->evStatContainer.verticeData[2 + (7 * 3)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 3)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 3)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 3)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 3)] = 0.0f;
				}

				// Bottom Right Point	4
				{
					data->evStatContainer.verticeData[0 + (7 * 4)] = xCenter + innerTriangleHeight;
					data->evStatContainer.verticeData[1 + (7 * 4)] = yCenter - (innerTriangleLineLength / 2.0f);
					data->evStatContainer.verticeData[2 + (7 * 4)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 4)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 4)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 4)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 4)] = 0.0f;
				}

				// Top Left Point		5
				{
					data->evStatContainer.verticeData[0 + (7 * 5)] = xCenter - innerTriangleHeight;
					data->evStatContainer.verticeData[1 + (7 * 5)] = yCenter + (innerTriangleLineLength / 2.0f);
					data->evStatContainer.verticeData[2 + (7 * 5)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 5)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 5)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 5)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 5)] = 0.0f;
				}

				// Bottom Left Point	6
				{
					data->evStatContainer.verticeData[0 + (7 * 6)] = xCenter - innerTriangleHeight;
					data->evStatContainer.verticeData[1 + (7 * 6)] = yCenter - (innerTriangleLineLength / 2.0f);
					data->evStatContainer.verticeData[2 + (7 * 6)] = 0.0f;
					data->evStatContainer.verticeData[3 + (7 * 6)] = colorMap[Color::WHITE].r;
					data->evStatContainer.verticeData[4 + (7 * 6)] = colorMap[Color::WHITE].g;
					data->evStatContainer.verticeData[5 + (7 * 6)] = colorMap[Color::WHITE].b;
					data->evStatContainer.verticeData[6 + (7 * 6)] = 0.0f;
				}
			}


			float statGraphLineLengthMax = innerTriangleLineLength;
			float statGraphLineLengthMin = resolution.y * (StatGraphBaseSize / 100.0f);
			float statGraphLineLengthDifference = statGraphLineLengthMax - statGraphLineLengthMin;

			float hpHeight = ((pokemon.getEvs().hp / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			
			float attackV = ((pokemon.getEvs().attack / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			float attackH = attackV * (sqrt(3) / 2.0f);
			
			float defenseV = ((pokemon.getEvs().defense / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			float defenseH = defenseV * (sqrt(3) / 2.0f);
			
			float speed = ((pokemon.getEvs().speed / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			
			float spDefV = ((pokemon.getEvs().spDefense / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			float spDefH = spDefV * (sqrt(3) / 2.0f);
			
			float spAttackV = ((pokemon.getEvs().spAttack / (float)evMax) * statGraphLineLengthDifference) + statGraphLineLengthMin;
			float spAttackH = spAttackV * (sqrt(3) / 2.0f);

			// Stat Graph
			{
				// Center				0
				{
					data->evStatGraph.verticeData[0] = xCenter;
					data->evStatGraph.verticeData[1] = yCenter;
					data->evStatGraph.verticeData[2] = 0.0f;
					data->evStatGraph.verticeData[3] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6] = 0.0f;
				}

				// Top Point			1		HP
				{
					data->evStatGraph.verticeData[0 + (7 * 1)] = xCenter;
					data->evStatGraph.verticeData[1 + (7 * 1)] = yCenter + hpHeight;
					data->evStatGraph.verticeData[2 + (7 * 1)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 1)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 1)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 1)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 1)] = 0.0f;
				}

				// Bottom Point			2		SPEED
				{
					data->evStatGraph.verticeData[0 + (7 * 2)] = xCenter;
					data->evStatGraph.verticeData[1 + (7 * 2)] = yCenter - speed;
					data->evStatGraph.verticeData[2 + (7 * 2)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 2)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 2)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 2)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 2)] = 0.0f;
				}

				// Top Right Point		3		ATTACK
				{
					data->evStatGraph.verticeData[0 + (7 * 3)] = xCenter + attackH;
					data->evStatGraph.verticeData[1 + (7 * 3)] = yCenter + (attackV / 2.0f);
					data->evStatGraph.verticeData[2 + (7 * 3)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 3)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 3)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 3)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 3)] = 0.0f;
				}

				// Bottom Right Point	4		DEFENSE
				{
					data->evStatGraph.verticeData[0 + (7 * 4)] = xCenter + defenseH;
					data->evStatGraph.verticeData[1 + (7 * 4)] = yCenter - (defenseV / 2.0f);
					data->evStatGraph.verticeData[2 + (7 * 4)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 4)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 4)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 4)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 4)] = 0.0f;
				}

				// Top Left Point		5		SPATTACK
				{
					data->evStatGraph.verticeData[0 + (7 * 5)] = xCenter - spAttackH;
					data->evStatGraph.verticeData[1 + (7 * 5)] = yCenter + (spAttackV / 2.0f);
					data->evStatGraph.verticeData[2 + (7 * 5)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 5)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 5)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 5)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 5)] = 0.0f;
				}

				// Bottom Left Point	6		SPDEFENSE
				{
					data->evStatGraph.verticeData[0 + (7 * 6)] = xCenter - spDefH;
					data->evStatGraph.verticeData[1 + (7 * 6)] = yCenter - (spDefV / 2.0f);
					data->evStatGraph.verticeData[2 + (7 * 6)] = 0.0f;
					data->evStatGraph.verticeData[3 + (7 * 6)] = colorMap[Color::GOLD].r;
					data->evStatGraph.verticeData[4 + (7 * 6)] = colorMap[Color::GOLD].g;
					data->evStatGraph.verticeData[5 + (7 * 6)] = colorMap[Color::GOLD].b;
					data->evStatGraph.verticeData[6 + (7 * 6)] = 0.0f;
				}
			}


			// Graph Text
			{
				float fontSize = ((triangleLineLength / resolution.y) * 100.0f) / fontDownSize;

				float textLineLength = resolution.y * ((GraphSizePercent + fontGraphOffset) / 100.0f);
				float textLineHeight = textLineLength * (sqrt(3) / 2.0f);

				float calculatedFontSize = (resolution.x * (fontSize / 100.0f));

				data->hpStatGraphData.value = "HP";
				data->attackStatGraphData.value = "ATTACK";
				data->defenseStatGraphData.value = "DEFENSE";
				data->speedStatGraphData.value = "SPEED";
				data->spDefStatGraphData.value = "SP.DEF";
				data->spAttackStatGraphData.value = "SP.ATK";

				data->hpStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter, resolution), getScreenYPercent(yCenter + textLineLength, resolution), fontSize, Color::BLACK, Alignment::CENTER_ALIGN };
				data->attackStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter + textLineHeight, resolution) , getScreenYPercent(yCenter + (textLineLength / 2.0f), resolution), fontSize, Color::BLACK, Alignment::LEFT_ALIGN };
				data->defenseStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter + textLineHeight, resolution), getScreenYPercent(yCenter - (textLineLength / 2.0f) - calculatedFontSize, resolution), fontSize, Color::BLACK, Alignment::LEFT_ALIGN };
				data->speedStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter, resolution), getScreenYPercent(yCenter - textLineLength - calculatedFontSize, resolution), fontSize, Color::BLACK, Alignment::CENTER_ALIGN };
				data->spDefStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter - textLineHeight, resolution), getScreenYPercent(yCenter - (textLineLength / 2.0f) - calculatedFontSize, resolution), fontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
				data->spAttackStatGraphData.renderData = TextBoxRenderData{ getScreenXPercent(xCenter - textLineHeight, resolution) , getScreenYPercent(yCenter + (textLineLength / 2.0f), resolution), fontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
			}
		}

		static void updatePokemonData(SummaryData* data, Pokemon pokemon, Resolution resolution)
		{
			data->type1.deleteWithScene = false;
			data->type2.deleteWithScene = false;

			data->evStatContainer.deleteWithScene = false;
			data->evStatContainerOutline.deleteWithScene = false;
			data->evStatGraph.deleteWithScene = false;


			data->moveData.pokemonName = pokemon.getName();

			// Type
			{
				float x = 50.0f;
				float y = 90.0f;
				float width = 5.0f;
				float height = 2.5f;

				data->type1.percentageX = x;
				data->type1.percentageY = y;
				data->type1.widthPercent = width;
				data->type1.heightPercent = height;
				data->type1.staticImage = g_typeTextureLocations[pokemon.getSpecies().type1];
				

				if (pokemon.getSpecies().type2 != Type::NONE)
				{
					data->type1.percentageX -= (width * 1.1f);

					data->type2.percentageX = x + (width * 1.1f);
					data->type2.percentageY = y;
					data->type2.widthPercent = width;
					data->type2.heightPercent = height;
					data->type2.staticImage = g_typeTextureLocations[pokemon.getSpecies().type2];
				}
			}
			
			int totalLength = 15;

			data->moveData.pokemonImageTextureLocation = pokemonFrontTexture(pokemon.getSpecies().name);
			
			data->statsData.level =	std::to_string(pokemon.getLevel());
			data->statsData.health =	std::to_string(pokemon.getCurHealth()) + "/" + std::to_string(pokemon.getStats().hp);
			data->statsData.attack =	std::to_string(pokemon.getStats().attack);
			data->statsData.defense =	std::to_string(pokemon.getStats().defense) ;
			data->statsData.spAttack =	std::to_string(pokemon.getStats().spAttack) ;
			data->statsData.spDefense = std::to_string(pokemon.getStats().spDefense) ;
			data->statsData.speed =	 	std::to_string(pokemon.getStats().speed) ;

			// Move 1
			{
				data->moveData.move1.moveName = getAttackFromID(pokemon.getMoveset().move1)->getName();
				data->moveData.move1.currentPP = std::to_string(pokemon.getMoveset().move1pp);
				data->moveData.move1.maxPP = std::to_string(getAttackFromID(pokemon.getMoveset().move1)->getPP());
				data->moveData.move1.moveTypeTextureLocation = g_typeTextureLocations[getAttackFromID(pokemon.getMoveset().move1)->getType()];
			}

			// Move 2
			{
				data->moveData.move2.moveName = getAttackFromID(pokemon.getMoveset().move2)->getName();
				data->moveData.move2.currentPP = std::to_string(pokemon.getMoveset().move2pp);
				data->moveData.move2.maxPP = std::to_string(getAttackFromID(pokemon.getMoveset().move2)->getPP());
				data->moveData.move2.moveTypeTextureLocation = g_typeTextureLocations[getAttackFromID(pokemon.getMoveset().move2)->getType()];
			}

			// Move 3
			{
				data->moveData.move3.moveName = getAttackFromID(pokemon.getMoveset().move3)->getName();
				data->moveData.move3.currentPP = std::to_string(pokemon.getMoveset().move3pp);
				data->moveData.move3.maxPP = std::to_string(getAttackFromID(pokemon.getMoveset().move3)->getPP());
				data->moveData.move3.moveTypeTextureLocation = g_typeTextureLocations[getAttackFromID(pokemon.getMoveset().move3)->getType()];
			}

			// Move 4
			{
				data->moveData.move4.moveName = getAttackFromID(pokemon.getMoveset().move4)->getName();
				data->moveData.move4.currentPP = std::to_string(pokemon.getMoveset().move4pp);
				data->moveData.move4.maxPP = std::to_string(getAttackFromID(pokemon.getMoveset().move4)->getPP());
				data->moveData.move4.moveTypeTextureLocation = g_typeTextureLocations[getAttackFromID(pokemon.getMoveset().move4)->getType()];
			}

			updatePokemonSummaryGraph(data, pokemon, resolution);
		}

		static void updateMoveData(int move, LearnMoveData* data, int currentHoverIndex)
		{
			data->move1OutlineVisiblity = false;
			data->move2OutlineVisiblity = false;
			data->move3OutlineVisiblity = false;
			data->move4OutlineVisiblity = false;

			if (currentHoverIndex == 0)
				data->move1OutlineVisiblity = true;
			else if (currentHoverIndex == 1)
				data->move2OutlineVisiblity = true;
			else if (currentHoverIndex == 2)
				data->move3OutlineVisiblity = true;
			else if (currentHoverIndex == 3)
				data->move4OutlineVisiblity = true;

			if (move == -1)
			{
				data->newMove.moveName = "NO DATA";
				data->power = "-";
				data->accuracy = "-";
				data->description = "";
				return;
			}

			data->newMove.moveName = getAttackFromID(move)->getName();
			data->power = std::to_string(getAttackFromID(move)->getPower());
			data->accuracy = std::to_string(getAttackFromID(move)->getAccuracy());
			data->description = getAttackFromID(move)->getDescription();
		}
	}

	static std::string keyboard(Menu* menu, MenuScene backgroundScene, std::string defaultText = "", bool canLeave = false)
	{
		//TODO: Enforce Name Size
		//TODO: Fix memory leak

		AlphabetStringData alphabetStringData;
		std::string keyboardText;

		menu->remove(MenuOverlay::ON_SCREEN_KEYBOARD);
		//menu->setupKeyboard(&alphabetStringData, &keyboardText);		//TODO: Move somewhere more accessible. Maybe keyboard class	//TODO: REMOVE
		MenuSetup::setupKeyboard(menu, &alphabetStringData, &keyboardText);


		//std::cout << "Keyboard Text Memory Location: " << &keyboardText << std::endl;
		std::string* text = &keyboardText;
		*text = defaultText;

		//std::cout << "Text Memory Location: " << text << std::endl;

		int selection = NONE;

		int buttonIndex = 0;

		menu->setRequestedData(&selection);
		menu->setCanLeave(false);
		menu->setscene(backgroundScene);
		menu->setOverlay(MenuOverlay::ON_SCREEN_KEYBOARD);
		menu->preRun();

		while (!menu->shouldClose())
		{
			buttonIndex = menu->getButtonIndex();
			menu->run();

			if (canLeave && menu->leaveRequested())
				break;

			if (selection == NONE)
				continue;

			if (selection == 39)
				swapAlphabetData(&alphabetStringData);
			else if (selection == 40)
				*text += " ";
			else if (selection == 41)
			{
				if (text->size() > 0)
					text->erase(text->begin() + text->size() - 1);
			}
			else if (selection == 42)
			{
				menu->setOverlay(MenuOverlay::NONE);
				menu->clearRequestedData();
				menu->postRun();
				menu->setCanLeave(true);
				return *text;
			}
			else
				*text += getKeyboardCharacter(&alphabetStringData, selection);

			selection = NONE;
			menu->setOverlay(MenuOverlay::ON_SCREEN_KEYBOARD);
			menu->setButtonIndex(buttonIndex);
		}

		menu->setOverlay(MenuOverlay::NONE);
		menu->clearRequestedData();
		menu->postRun();
		menu->setCanLeave(true);

		return "!";
	};

	static void pokemonSummary(Menu* menu, Pokemon pokemon) {

		SummaryData data;
		int hoveredButton = 0;
		int prevHoverIndex = NONE;

		// Update the pokemon Data
		updatePokemonData(&data, pokemon, menu->getResolution());

		menu->remove(MenuScene::POKEMON_SUMMARY);
		//menu->setupSummaryData(&data);	//TODO: REMOVE
		MenuSetup::setupSummaryData(menu, &data);
		menu->setRequestedData(&hoveredButton);

		menu->setCanLeave(false);
		menu->setscene(MenuScene::POKEMON_SUMMARY);
		menu->setOverlay(MenuOverlay::NONE);
		menu->preRun();

		
		

		while (!menu->shouldClose())
		{
			if (menu->getCurrentScene() != MenuScene::POKEMON_SUMMARY)
			{
				menu->setscene(MenuScene::POKEMON_SUMMARY);
				menu->setButtonIndex(hoveredButton);
			}

			menu->run();

			if (menu->leaveRequested())
				break;

			hoveredButton = menu->getButtonIndex();

			if (hoveredButton == prevHoverIndex)
				continue;


			// Update the move data

			int moveID = 0;
			switch (hoveredButton)
			{
			case 0:
				moveID = pokemon.getMoveset().move1;
				break;
			case 1:
				moveID = pokemon.getMoveset().move2;
				break;
			case 2:
				moveID = pokemon.getMoveset().move3;
				break;
			case 3:
				moveID = pokemon.getMoveset().move4;
				break;
			default:
				moveID = -1;
				break;
			}

			updateMoveData(moveID, &data.moveData, hoveredButton);

			prevHoverIndex = hoveredButton;
		}

		menu->clearRequestedData();
		menu->postRun();
		menu->setCanLeave(true);
	};

	static void trainerRoster(Menu* menu, Trainer* trainer, bool canSelectOptions) {
	
	}

	static bool getPlayerGenderIsMale(Menu* menu)
	{
		int selection = NONE;
		
		bool showFemaleHighlight = true;
		bool showMaleHighlight = false;

		MenuSetup::setupSelectPlayerGender(menu, &showMaleHighlight, &showFemaleHighlight);
		//menu->setupSelectPlayerGender(&showMaleHighlight, &showFemaleHighlight);		//TODO: REMOVE
		menu->setRequestedData(&selection);

		menu->setCanLeave(false);
		menu->setscene(MenuScene::SELECT_PLAYER_GENDER);
		menu->preRun();

		int hoverButton = menu->getButtonIndex();

		while (!menu->shouldClose())
		{
			menu->run();

			if (selection != NONE)
			{
				if (selection == 0)
					return false;
				return true;
			}

			if (menu->getButtonIndex() != hoverButton)
			{
				hoverButton = menu->getButtonIndex();

				showFemaleHighlight = !showFemaleHighlight;
				showMaleHighlight = !showMaleHighlight;
			}
		}

		menu->postRun();

		menu->remove(MenuScene::SELECT_PLAYER_GENDER);
		return true;
	}

	static void playerAcquireArtifact(std::string artifactName, std::string artifactImagePath, std::vector<std::string> additionalComments, MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer)
	{
		int selection = NONE;

		//TODO: Will need to change image visiblity and move text on screen or setup another menu function for this data

		AcquireItemData data;

		data.itemName = artifactName;
		data.itemLocation = artifactImagePath;

		MenuSetup::setupPlayerAcqiuresItem(menu, &data);
		//menu->setupPlayerAcqiuresItem(&data);		//TODO: REMOVE
		menu->setRequestedData(&selection);

		menu->setCanLeave(false);
		menu->setOverlay(MenuOverlay::PLAYER_ACQUIRE_ITEM);
		menu->preRun();

		mapHandler->onUpdate();
		trainer->onUpdate(renderer);

		while (!menu->shouldClose())
		{
			menu->run();

			if (selection != NONE)
				break;

			mapHandler->onUpdate();
			trainer->onUpdate(renderer);
		}

		renderer->onUpdate();

		menu->postRun();

		menu->remove(MenuOverlay::PLAYER_ACQUIRE_ITEM);
	}

	static void adjustSpeakerNameContainer(std::string text, float fontSize, float textLength, PolygonData* data, float screenX, float leftAlignPercent, float bottomHeightPercent )
	{
		float widthPaddingPercent = 1.0f;
		float heightPaddingPercent = 1.0f;
		float trapezoidLengthPercent = 2.0f;
		float blackOutlinePercent = 0.5f;

		unsigned int pixelSize = (unsigned int)(screenX * (fontSize / 100.0f));

		float totalSize = textLength;

		unsigned int widthPad = (unsigned int)(screenX * (widthPaddingPercent / 100.0f));
		unsigned int heightPad = (unsigned int)(screenX * (heightPaddingPercent / 100.0f));
		unsigned int trapPad = (unsigned int)(screenX * (trapezoidLengthPercent / 100.0f));
		unsigned int outlinePad = (unsigned int)(screenX * (blackOutlinePercent / 100.0f));
		float leftSidePixel = (screenX * (leftAlignPercent / 100.0f));
		float bottomPixel = (screenX * (bottomHeightPercent / 100.0f));

		//							RISE										/				RUN
		// Positive Slope Of Sides
		float slope = abs(((bottomPixel + pixelSize + heightPad) - (bottomPixel)) / ((leftSidePixel + totalSize + widthPad + outlinePad)-(leftSidePixel + totalSize + widthPad + trapPad + outlinePad)));

		float leftSideIncrease = outlinePad / slope;
		float rightSideIncrease = outlinePad / (-1 * slope);

		std::vector<GLuint> indices =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7
		};

		for (int i = 0; i < indices.size(); i++)
			data->indiceData[i] = indices.at(i);

		data->visible = true;
		data->indicesToDraw = 12;

		// Black Outline
		{
			//						0
			{
				data->verticeData[0 + (7 * 0)] = leftSidePixel - outlinePad + leftSideIncrease;
				data->verticeData[1 + (7 * 0)] = bottomPixel + pixelSize + heightPad + outlinePad;
				data->verticeData[2 + (7 * 0)] = 0.0f;
				data->verticeData[3 + (7 * 0)] = colorMap[Color::BLACK].r;
				data->verticeData[4 + (7 * 0)] = colorMap[Color::BLACK].g;
				data->verticeData[5 + (7 * 0)] = colorMap[Color::BLACK].b;
				data->verticeData[6 + (7 * 0)] = 0.0f;
			}

			//						1
			{
				data->verticeData[0 + (7 * 1)] = leftSidePixel + totalSize + widthPad + outlinePad + rightSideIncrease;
				data->verticeData[1 + (7 * 1)] = bottomPixel + pixelSize + heightPad + outlinePad;
				data->verticeData[2 + (7 * 1)] = 0.0f;
				data->verticeData[3 + (7 * 1)] = colorMap[Color::BLACK].r;
				data->verticeData[4 + (7 * 1)] = colorMap[Color::BLACK].g;
				data->verticeData[5 + (7 * 1)] = colorMap[Color::BLACK].b;
				data->verticeData[6 + (7 * 1)] = 0.0f;
			}

			//						2
			{
				data->verticeData[0 + (7 * 2)] = leftSidePixel + totalSize + widthPad + trapPad + outlinePad;
				data->verticeData[1 + (7 * 2)] = bottomPixel;
				data->verticeData[2 + (7 * 2)] = 0.0f;
				data->verticeData[3 + (7 * 2)] = colorMap[Color::BLACK].r;
				data->verticeData[4 + (7 * 2)] = colorMap[Color::BLACK].g;
				data->verticeData[5 + (7 * 2)] = colorMap[Color::BLACK].b;
				data->verticeData[6 + (7 * 2)] = 0.0f;
			}

			//						3
			{
				data->verticeData[0 + (7 * 3)] = leftSidePixel - trapPad - outlinePad;
				data->verticeData[1 + (7 * 3)] = bottomPixel;
				data->verticeData[2 + (7 * 3)] = 0.0f;
				data->verticeData[3 + (7 * 3)] = colorMap[Color::BLACK].r;
				data->verticeData[4 + (7 * 3)] = colorMap[Color::BLACK].g;
				data->verticeData[5 + (7 * 3)] = colorMap[Color::BLACK].b;
				data->verticeData[6 + (7 * 3)] = 0.0f;
			}
		}

		// Inner White
		{
			//						4
			{
				data->verticeData[0 + (7 * 4)] = leftSidePixel;
				data->verticeData[1 + (7 * 4)] = bottomPixel + pixelSize + heightPad;
				data->verticeData[2 + (7 * 4)] = 0.0f;
				data->verticeData[3 + (7 * 4)] = colorMap[Color::WHITE].r;
				data->verticeData[4 + (7 * 4)] = colorMap[Color::WHITE].g;
				data->verticeData[5 + (7 * 4)] = colorMap[Color::WHITE].b;
				data->verticeData[6 + (7 * 4)] = 0.0f;
			}

			//						5
			{
				data->verticeData[0 + (7 * 5)] = leftSidePixel + totalSize + widthPad;
				data->verticeData[1 + (7 * 5)] = bottomPixel + pixelSize + heightPad;
				data->verticeData[2 + (7 * 5)] = 0.0f;
				data->verticeData[3 + (7 * 5)] = colorMap[Color::WHITE].r;
				data->verticeData[4 + (7 * 5)] = colorMap[Color::WHITE].g;
				data->verticeData[5 + (7 * 5)] = colorMap[Color::WHITE].b;
				data->verticeData[6 + (7 * 5)] = 0.0f;
			}

			//						6
			{
				data->verticeData[0 + (7 * 6)] = leftSidePixel + totalSize + widthPad + trapPad;
				data->verticeData[1 + (7 * 6)] = bottomPixel;
				data->verticeData[2 + (7 * 6)] = 0.0f;
				data->verticeData[3 + (7 * 6)] = colorMap[Color::WHITE].r;
				data->verticeData[4 + (7 * 6)] = colorMap[Color::WHITE].g;
				data->verticeData[5 + (7 * 6)] = colorMap[Color::WHITE].b;
				data->verticeData[6 + (7 * 6)] = 0.0f;
			}

			//						7
			{
				data->verticeData[0 + (7 * 7)] = leftSidePixel - trapPad;
				data->verticeData[1 + (7 * 7)] = bottomPixel;
				data->verticeData[2 + (7 * 7)] = 0.0f;
				data->verticeData[3 + (7 * 7)] = colorMap[Color::WHITE].r;
				data->verticeData[4 + (7 * 7)] = colorMap[Color::WHITE].g;
				data->verticeData[5 + (7 * 7)] = colorMap[Color::WHITE].b;
				data->verticeData[6 + (7 * 3)] = 0.0f;
			}
		}
		

	}

	static int displayRosterOptions(std::vector<std::string> options, int rosterIndex, Menu* menu, Renderer* renderer)
	{
		MenuSetup::setupRosterOptions(menu, options);
		//menu->setupRosterOptions(options);		//TODO: REMOVE
		
		int selection = NONE;

		menu->setRequestedData(&selection);
		menu->setOverlay(MenuOverlay::ROSTER_OPTIONS);
		menu->setCanLeave(false);
		menu->preRun();

		while (true)
		{
			menu->run();

			if (menu->shouldClose())
				return -1;

			if (menu->leaveRequested())
				break;

			if (selection == NONE)
				continue;

			break;
		}

		menu->clearRequestedData();
		menu->clearScenes();
		menu->postRun();

		menu->setOverlay(MenuOverlay::NONE);
		menu->remove(MenuOverlay::ROSTER_OPTIONS);

		return selection;
	}
}

