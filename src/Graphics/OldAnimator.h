#pragma once

#include "Renderer.h"
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <chrono>
#include <deque>
#include <condition_variable>

enum class Animation
{
	NONE,
	STREAM_END,
	FADE_IN,
	FADE_OUT,
	LEGENDARY_STUDIO,
	LEGENDARY_POKEMON,
	THROW_POKEBALL,
	THROW_GREATBALL,
	THROW_ULTRABALL,
	THROW_MASTERBALL,
	ESCAPE_POKEBALL,
	ESCAPE_GREATBALL,
	ESCAPE_ULTRABALL,
	ESCAPE_MASTERBALL,
	XP_GAIN,
	XP_LEVEL_UP_UI,
	GRASS_ENCOUNTER
};

class OldAnimator
{
public:
	OldAnimator() {};

	~OldAnimator()
	{
		while (!loadingComplete()) {}
		while (!unloadingComplete()) {}
	}

	void setup(Renderer* renderer, Timer* timer)
	{
		m_renderer = renderer;
		m_timer = timer;
	}

	int getFrameCount() { return m_currentFrameCount; }
	void setPauseAnimation(bool pause) { m_pauseAnimation = pause; }


	void loadAnimation(Animation animation) { loadAnimations(std::vector<Animation> {animation}); }
	void loadAnimations(std::vector<Animation> animations) {
		//TODO: Have the thread wait while loading completes. This way we dont try to load something and it just returns because it cant
		if (!loadingComplete() || !unloadingComplete())
			return;

		m_loadingComplete = false;
		std::cout << "Load Thread About to start" << std::endl;
		m_loadThread = std::thread(&OldAnimator::loadThread, this, animations);
		std::cout << "Load Thread started" << std::endl;
	}

	void unloadAnimation(Animation animation) { unloadAnimations(std::vector<Animation> {animation}); }
	void unloadAnimations(std::vector<Animation> animations)
	{
		if (!unloadingComplete())
			return;

		m_unloadingComplete = false;

		std::cout << "Unload Thread About to start" << std::endl;
		m_loadThread = std::thread(&OldAnimator::unloadThread, this, animations);
		std::cout << "Unload Thread started" << std::endl;

	}

	void setAnimation(Animation animation, bool loopAnimation = false)
	{
		//TODO: Check in the future if the animation is already loaded. If it is loaded then do not reload the function
		//			- Possibly check if there is anything being unloaded. Because if it is being unloaded then we would want to reload it.
		//			- A function asking if we are unloading similar to if we have completed our load would help with this

		m_currentAnimation = animation;
		m_currentFrameCount = 0;
		m_animationFrames = &m_loadedAnimations[animation];

		m_countTarget = 1.0f / (float)m_animations[animation].fps;
		m_count = m_countTarget;

		m_loop = loopAnimation;
	};

	bool loadingComplete() {

		if (m_loadingComplete && m_loadThread.joinable())
		{
			m_loadThread.join();
			std::cout << "Load Thread Joined" << std::endl;
		}

		return m_loadingComplete;
	};

	bool unloadingComplete() {
		if (m_unloadingComplete && m_unloadThread.joinable())
		{
			m_unloadThread.join();
			std::cout << "Unload Thread Joined" << std::endl;
		}
		return m_unloadingComplete;
	};

	void playAnimation()
	{

		if (!animationPlaying())
		{
			if (m_loop)
			{
				m_currentFrameCount = 0;
				m_count = m_countTarget;
			}
			else
				return;
		}

		if (m_count >= m_countTarget)
		{
			//NOTE: I originally had it as m_loadedAnimations[m_currentAnimation].at(m_currentFrameCount) but in my mind the animation looks worse so I added this vector* :)
			m_renderer->renderTexture(&m_animationFrames->at(m_currentFrameCount));

			if (m_pauseAnimation)
				return;

			m_currentFrameCount++;
			m_count = 0.0f;
		}
		else
		{
			m_renderer->renderTexture(&m_animationFrames->at(m_currentFrameCount));

			if (m_pauseAnimation)
				return;

			m_count += m_timer->getDelta();
		}

	}

	void updateRenderer() { m_renderer->onUpdate(); };

	bool animationPlaying() { return m_currentFrameCount < m_animations[m_currentAnimation].frameCount; }

private:

	void loadThread(std::vector<Animation> animations)
	{
		glfwMakeContextCurrent(m_renderer->getSharedWindow());
		glewInit();

		GLenum returnCode = glewInit();

		std::cout << "Return Code Old: " << returnCode << std::endl;

		if (returnCode != GLEW_OK)
		{
			glfwMakeContextCurrent(NULL);
			exit(returnCode);
		}

		while (!unloadingComplete()) { std::this_thread::sleep_for(std::chrono::milliseconds(200)); }

		for (Animation animation : animations)
		{
			std::string path = m_animationDir + m_animations[animation].name + "/" + m_animations[animation].name + "_";

			m_loadedAnimations[animation] = std::vector<Texture>();


			for (int i = 0; i < m_animations[animation].frameCount; i++)
			{
				std::string animationPath = path + std::to_string(i) + ".png";
				m_loadedAnimations[animation].push_back(Texture(animationPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE));
			}
		}

		m_loadingComplete = true;
		glfwMakeContextCurrent(NULL);
	}

	void unloadThread(std::vector<Animation> animations)
	{
		for (Animation animation : animations)
		{
			for (int i = 0; i < m_animations[animation].frameCount; i++)
			{
				m_loadedAnimations[animation].at(0).Delete();
				m_loadedAnimations[animation].erase(m_loadedAnimations[animation].begin());
			}
			m_loadedAnimations.erase(animation);
		}

		m_unloadingComplete = true;
	}

private:
	Renderer* m_renderer = nullptr;
	Timer* m_timer = nullptr;
	std::string m_animationDir = "Animations/";

	Animation m_currentAnimation = Animation::LEGENDARY_STUDIO;
	std::vector<Texture>* m_animationFrames = nullptr;
	int m_currentFrameCount = 0;
	float m_count = 0.0f;
	float m_countTarget = 0.0f;

	bool m_loadingComplete = true;
	bool m_unloadingComplete = true;
	bool m_loop = false;
	bool m_pauseAnimation = false;

	std::thread m_loadThread;
	std::thread m_unloadThread;


	struct AnimationData
	{
		std::string name;
		int frameCount;
		int fps;
	};

	std::unordered_map<Animation, AnimationData> m_animations
	{
		{Animation::LEGENDARY_STUDIO,	{"LegendaryStudio",		43,		15}},
		{Animation::FADE_IN,			{"FadeIn",				51,		60}},
		{Animation::FADE_OUT,			{"FadeOut",				51,		60}},
		{Animation::LEGENDARY_POKEMON,	{"AganiteIntro",		47,		7}},
		{Animation::THROW_POKEBALL,		{"ThrowPokeball",		106,	12}},
		{Animation::THROW_GREATBALL,	{"ThrowGreatball",		106,	12}},
		{Animation::THROW_ULTRABALL,	{"ThrowUltraball",		106,	12}},
		{Animation::THROW_MASTERBALL,	{"ThrowMasterball",		106,	12}},
		{Animation::ESCAPE_POKEBALL,	{"EscapePokeball",		9,		12}},
		{Animation::ESCAPE_GREATBALL,	{"EscapeGreatball",		9,		12}},
		{Animation::ESCAPE_ULTRABALL,	{"EscapeUltraball",		9,		12}},
		{Animation::ESCAPE_MASTERBALL,	{"EscapeMasterball",	9,		12}},
		{Animation::XP_GAIN,			{"XpGain",				20,		12}},
		{Animation::XP_LEVEL_UP_UI,		{"XpLevelUpUI",			19,		60}},
	};

	std::unordered_map<Animation, std::vector<Texture>> m_loadedAnimations{};
};