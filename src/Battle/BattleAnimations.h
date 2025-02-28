#pragma once
#include "../Graphics/PositionalData.h"

//TODO: Rename to Battle Pokemon Animations or something so that its not confused with menu graphics or animation class
namespace BattleAnimations
{
	namespace
	{	
		static int m_playerPokemonPercentageX = 25.5f;
		static int m_playerPokemonPercentageY = (253.5f / 563.0f) * 100.0f;
		static int m_playerPokemonWidthPercent = 20.0f * (9.0f / 16.0f);
		static int m_playerPokemonHeightPercent = 20.0f;

		static int m_opponentPokemonPercentageX = 74.4f;
		static int m_opponentPokemonPercentageY = (443.0f / 563.0f) * 100.0f;
		static int m_opponentPokemonWidthPercent = 10.0f;
		static int m_opponentPokemonHeightPercent = 10.0f * (16.0f / 9.0f);
		


		static int m_catchFrame = 30;
		static int m_catchDuration = 7;

		static int m_releaseFrame = 0;
		static int m_releaseDuration = 8; //TODO: Maybe 5

		static int m_opponentFaintFrame = 0;
		static int m_opponentFaintDuration = 14;

		static int m_playerFaintFrame = 0;
		static int m_playerFaintDuration = 15;

		static int m_playerWithdrawFrame = 0;
		static int m_playerWithdrawDuration = 14;

		static int m_playerSendOutPokemonFrame = 0;
		static int m_playerSendOutPokemonDuration = 14;

		static int m_opponentSendOutPokemonFrame = 0;
		static int m_opponentSendOutPokemonDuration = 14;

		static int m_pokemonTakeDamageFrame = 0;
		static int m_pokemonTakeDamageDuration = 10;
		static int m_pokemonTakeDamageCycles = 3;

		static int m_pokemonGrowShrinkDuration = 10;
		static int m_pokemonColorChangeDuration = 10;

	}

	static void wildPokemonIntoPokeball(int frame, DynamicImageRenderData* wildPokemonData)
	{
		if (frame < m_catchFrame || frame > m_catchFrame + m_catchDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_catchDuration;

		int differenceDown = m_catchDuration - (frame - m_catchFrame);
		int differenceUp = frame - m_catchFrame;

		float dimensionMultiplier = frameMultiplier * differenceDown;

		wildPokemonData->widthPercent = m_opponentPokemonWidthPercent * dimensionMultiplier;
		wildPokemonData->heightPercent = m_opponentPokemonHeightPercent * dimensionMultiplier;

		{
			float currentXPercent = m_opponentPokemonPercentageX;
			float ballXPercent = ((740.0f / 1000.0f) * 100.0f);

			float amountToMove = ballXPercent - currentXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageX = currentXPercent + perFrameMovePercent;
		}
		

		{
			float currentYPercent = m_opponentPokemonPercentageY;
			float ballYPercent = ((523.0f / 563.0f) * 100.0f);

			float amountToMove = ballYPercent - currentYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageY = currentYPercent + perFrameMovePercentY;
		}

		{
			float amountToIncrease = 0.3f * frameMultiplier * differenceUp;
			wildPokemonData->color.r = 0.7f + amountToIncrease;
		}
	}

	static void wildPokemonEscapePokeball(int frame, DynamicImageRenderData* wildPokemonData)
	{
		if (frame < m_releaseFrame || frame > m_releaseFrame + m_releaseDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_releaseDuration;
		int differenceUp =  frame - m_releaseFrame;
		int differenceDown = m_releaseDuration - (frame - m_releaseFrame);

		float dimensionMultiplier = frameMultiplier * differenceUp;

		wildPokemonData->widthPercent = m_opponentPokemonWidthPercent * dimensionMultiplier;
		wildPokemonData->heightPercent = m_opponentPokemonHeightPercent * dimensionMultiplier;

		{
			float originalXPercent = m_opponentPokemonPercentageX;
			float ballXPercent = ((741.0f / 1000.0f) * 100.0f);

			float amountToMove = originalXPercent - ballXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageX = ballXPercent + perFrameMovePercent;
		}


		{
			float originalYPercent = m_opponentPokemonPercentageY;
			float ballYPercent = ((403.0f / 563.0f) * 100.0f);

			float amountToMove = originalYPercent - ballYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageY = ballYPercent + perFrameMovePercentY;
		}

		{
			float amountToDecrease = 1.0f * frameMultiplier * differenceUp;
			wildPokemonData->color.r = 1.0f - amountToDecrease;
		}
	}

	static void opponentPokemonFaint(int frame, DynamicImageRenderData* opponentPokemonData)
	{
		if (frame < m_opponentFaintFrame || frame > m_opponentFaintFrame + m_opponentFaintDuration)
			return;
		
		float frameMultiplier = 1.0f / (float)m_opponentFaintDuration;
		
		int differenceDown = m_opponentFaintDuration - (frame - m_opponentFaintFrame);
		int differenceUp = frame - m_opponentFaintFrame;
		
		float dimensionMultiplier = frameMultiplier * differenceDown;

		float heightPercentDifference = (m_opponentPokemonHeightPercent) * (frameMultiplier * differenceUp);

		opponentPokemonData->heightPercent = (m_opponentPokemonHeightPercent) - (heightPercentDifference);
		opponentPokemonData->percentageY = m_opponentPokemonPercentageY - heightPercentDifference;
		opponentPokemonData->imageTextureCoords.bottomLeftY = 1.0f - (1.0f * dimensionMultiplier);
		opponentPokemonData->imageTextureCoords.bottomRightY = 1.0f - (1.0f * dimensionMultiplier);
	}

	static void playerPokemonFaint(int frame, DynamicImageRenderData* playerPokemonData)
	{
		if (frame < m_playerFaintFrame || frame > m_playerFaintFrame + m_playerFaintDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_playerFaintDuration;

		int differenceDown = m_playerFaintDuration - (frame - m_playerFaintFrame);
		int differenceUp = frame - m_playerFaintFrame;

		float dimensionMultiplier = frameMultiplier * differenceDown;

		float heightPercentDifference = m_playerPokemonHeightPercent * (frameMultiplier * differenceUp);

		playerPokemonData->heightPercent = m_playerPokemonHeightPercent - (heightPercentDifference);
		playerPokemonData->percentageY = (m_playerPokemonPercentageY)  - heightPercentDifference;
		playerPokemonData->imageTextureCoords.bottomLeftY = 1.0f - (1.0f * dimensionMultiplier);
		playerPokemonData->imageTextureCoords.bottomRightY = 1.0f - (1.0f * dimensionMultiplier);
	}

	static void playerPokemonWithdraw(int frame, DynamicImageRenderData* playerPokemonData)
	{
		if (frame < m_playerWithdrawFrame || frame > m_playerWithdrawFrame + m_playerWithdrawDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_playerWithdrawDuration;

		int differenceDown = m_playerWithdrawDuration - (frame - m_playerWithdrawFrame);
		int differenceUp = frame - m_playerWithdrawFrame;

		float dimensionMultiplier = frameMultiplier * differenceDown;

		playerPokemonData->widthPercent = m_playerPokemonWidthPercent * dimensionMultiplier;
		playerPokemonData->heightPercent = m_playerPokemonHeightPercent * dimensionMultiplier;

		{
			float currentXPercent = m_playerPokemonPercentageX;
			float ballXPercent = ((50.0f / 1000.0f) * 100.0f);

			float amountToMove = ballXPercent - currentXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			playerPokemonData->percentageX = currentXPercent + perFrameMovePercent;
		}


		{
			float currentYPercent = m_playerPokemonPercentageY;
			float ballYPercent = ((300.5f / 563.0f) * 100.0f);

			float amountToMove = ballYPercent - currentYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			playerPokemonData->percentageY = currentYPercent + perFrameMovePercentY;
		}

		{
			float amountToIncrease = 0.5f * frameMultiplier * differenceUp;
			playerPokemonData->color.r = 0.5f + amountToIncrease;
		}
	}

	static void sendOutPlayerPokemon(int frame, DynamicImageRenderData* playerPokemonData)
	{
		if (frame < m_playerSendOutPokemonFrame || frame > m_playerSendOutPokemonFrame + m_playerSendOutPokemonDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_playerSendOutPokemonDuration;
		int differenceUp = frame - m_playerSendOutPokemonFrame;
		int differenceDown = m_playerSendOutPokemonDuration - (frame - m_playerSendOutPokemonFrame);

		float dimensionMultiplier = frameMultiplier * differenceUp;

		

		playerPokemonData->imageTextureCoords = ImageTextureCoords{};
		playerPokemonData->widthPercent = m_playerPokemonWidthPercent * dimensionMultiplier;
		playerPokemonData->heightPercent = m_playerPokemonHeightPercent * dimensionMultiplier;

		{
			float originalXPercent = m_playerPokemonPercentageX;
			float ballXPercent = ((250.0f / 1000.0f) * 100.0f);

			float amountToMove = originalXPercent - ballXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			playerPokemonData->percentageX = ballXPercent + perFrameMovePercent;
		}


		{
			float originalYPercent = m_playerPokemonPercentageY;
			float ballYPercent = (150.0f / 563.0f) * 100.0f;

			float amountToMove = originalYPercent - ballYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			playerPokemonData->percentageY = ballYPercent + perFrameMovePercentY;
		}

		{
			float amountToDecrease = 1.0f * frameMultiplier * differenceUp;
			playerPokemonData->color.r = 1.0f - amountToDecrease;
		}
	}

	static void sendOutOpponentPokemon(int frame, DynamicImageRenderData* opponentPokemonData)
	{
		if (frame < m_playerSendOutPokemonFrame || frame > m_playerSendOutPokemonFrame + m_playerSendOutPokemonDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_playerSendOutPokemonDuration;
		int differenceUp = frame - m_playerSendOutPokemonFrame;
		int differenceDown = m_playerSendOutPokemonDuration - (frame - m_playerSendOutPokemonFrame);

		float dimensionMultiplier = frameMultiplier * differenceUp;

		opponentPokemonData->imageTextureCoords = ImageTextureCoords{};
		opponentPokemonData->widthPercent = m_opponentPokemonWidthPercent * dimensionMultiplier;
		opponentPokemonData->heightPercent = m_opponentPokemonHeightPercent * dimensionMultiplier;

		{
			float originalXPercent = m_opponentPokemonPercentageX;
			float ballXPercent = ((741.0f / 1000.0f) * 100.0f);

			float amountToMove = originalXPercent - ballXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			opponentPokemonData->percentageX = ballXPercent + perFrameMovePercent;
		}


		{
			float originalYPercent = m_opponentPokemonPercentageY;
			float ballYPercent = ((403.0f / 563.0f) * 100.0f);

			float amountToMove = originalYPercent - ballYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			opponentPokemonData->percentageY = ballYPercent + perFrameMovePercentY;
		}

		{
			float amountToDecrease = 1.0f * frameMultiplier * differenceUp;
			opponentPokemonData->color.r = 1.0f - amountToDecrease;
		}
	}

	static void playerPokemonTakeDamage(int frame, DynamicImageRenderData* playerPokemonData)
	{
		if (frame < m_pokemonTakeDamageFrame)
			return;

		float localFrameCount = (frame - m_pokemonTakeDamageFrame + 1) % m_pokemonTakeDamageCycles;
		float localDuration = floor((float)m_pokemonTakeDamageDuration / (float)m_pokemonTakeDamageCycles);
		float startDamageTriggerPercent = 30.0f;
		float stopDamageTriggerPercent = 70.0f;

		float currentPercent = (localFrameCount / localDuration) * 100.0f;

		if (startDamageTriggerPercent <= currentPercent && currentPercent <= stopDamageTriggerPercent)
			playerPokemonData->alpha = 255.0;
		else
			playerPokemonData->alpha = 0.0f;
	}

	static void opponentPokemonTakeDamage(int frame, DynamicImageRenderData* opponentPokemonData)
	{
		if (frame < m_pokemonTakeDamageFrame)
			return;

		float localFrameCount = (frame - m_pokemonTakeDamageFrame + 1) % m_pokemonTakeDamageCycles;
		float localDuration = floor((float)m_pokemonTakeDamageDuration / (float)m_pokemonTakeDamageCycles);
		float startDamageTriggerPercent = 30.0f;
		float stopDamageTriggerPercent = 70.0f;

		float currentPercent = (localFrameCount / localDuration) * 100.0f;

		if (startDamageTriggerPercent <= currentPercent && currentPercent <= stopDamageTriggerPercent)
			opponentPokemonData->alpha = 255.0f;
		else
			opponentPokemonData->alpha = 0.0f;
	}

	static void growEvolutionPokemon(int frame, DynamicImageRenderData* pokemonData)
	{
		//TODO: Doesnt Shrink to Desired value. Shrinks to ambiguous value based on shrink duration

		float frameMultiplier = 1.0f / (float)m_pokemonGrowShrinkDuration;
		float dimensionMultiplier = frame * frameMultiplier;

		pokemonData->widthPercent = 9.0f * dimensionMultiplier;
		pokemonData->heightPercent = 16.0f * dimensionMultiplier;
		pokemonData->alpha = 0.0f;
	}

	static void shrinkEvolutionPokemon(int frame, DynamicImageRenderData* pokemonData)
	{
		//TODO: Doesnt Shrink to Desired value. Shrinks to ambiguous value based on shrink duration
		float frameMultiplier = 1.0f / (float)m_pokemonGrowShrinkDuration;
		float dimensionMultiplier = (m_pokemonGrowShrinkDuration - frame) * frameMultiplier;

		pokemonData->widthPercent = 9.0f * dimensionMultiplier;
		pokemonData->heightPercent = 16.0f * dimensionMultiplier;

		if (frame == m_pokemonGrowShrinkDuration)
			pokemonData->alpha = 255.0f;
	}

	static void normalToWhite(int frame, DynamicImageRenderData* pokemonData)
	{
		float frameMultiplier = 1.0f / (float)m_pokemonColorChangeDuration;
		float dimensionMultiplier = frame * frameMultiplier;

		float value = 1.0f * dimensionMultiplier;

		pokemonData->color = glm::vec4(value, value, value, 0.0f);
	}

	static void WhiteToNormal(int frame, DynamicImageRenderData* pokemonData)
	{
		float frameMultiplier = 1.0f / (float)m_pokemonColorChangeDuration;
		float dimensionMultiplier = (m_pokemonColorChangeDuration - frame) * frameMultiplier;

		float value = 1.0f * dimensionMultiplier;

		pokemonData->color = glm::vec4(value, value, value, 0.0f);
	}
}