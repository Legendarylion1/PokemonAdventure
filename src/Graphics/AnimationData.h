#pragma once
#include "OldAnimator.h"

struct AnimationData
{
	std::string name;
	int frameCount;
	int fps;
};

static AnimationData getAnimationData(Animation animation)
{
	switch (animation)
	{
	case Animation::LEGENDARY_STUDIO:
		return {"LegendaryStudio", 43, 15};
	case Animation::FADE_IN:
		return {"FadeIn", 51, 60};
	case Animation::FADE_OUT:
		return { "FadeOut", 51, 60};
	case Animation::LEGENDARY_POKEMON:
		return { "AganiteIntro", 47, 7};
	case Animation::THROW_POKEBALL:
		return { "ThrowPokeball", 106, 12};
	case Animation::THROW_GREATBALL:
		return { "ThrowGreatball", 106, 12};
	case Animation::THROW_ULTRABALL:
		return { "ThrowUltraball", 106, 12};
	case Animation::THROW_MASTERBALL:
		return { "ThrowMasterball", 106, 12};
	case Animation::ESCAPE_POKEBALL:
		return { "EscapePokeball", 9, 12};
	case Animation::ESCAPE_GREATBALL:
		return { "EscapeGreatball", 9, 12 };
	case Animation::ESCAPE_ULTRABALL:
		return { "EscapeUltraball", 9, 12 };
	case Animation::ESCAPE_MASTERBALL:
		return { "EscapeMasterball", 9, 12 };
	case Animation::XP_GAIN:
		return { "XpGain", 20, 12 };
	case Animation::XP_LEVEL_UP_UI:
		return { "XpLevelUpUI", 19, 60 };
	case Animation::GRASS_ENCOUNTER:
		return { "grassEncounter", 81, 60 };
	default:
		return {};
	}
}