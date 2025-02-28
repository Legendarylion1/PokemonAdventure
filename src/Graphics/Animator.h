#pragma once
#include "Semaphore.h"
#include "AnimationData.h"
#include <queue>

enum class AnimationJobType
{
	LOAD,
	UNLOAD
};

struct AnimationJob
{
	AnimationJobType type;
	Animation animation;
};

class Animator
{
public:
	Animator() {};

	~Animator()
	{
		m_stopAnimation = true;

		pushJob({AnimationJobType::LOAD, Animation::STREAM_END });

		while (!m_loadingComplete) {}

		m_loadThread.join();
	}

	void setup(Renderer* renderer, Timer* timer)
	{
		//TODO: Move to constructor
		m_renderer = renderer;
		m_timer = timer;

		m_loadThread = std::thread(&Animator::animationJobThread, this);

		while (!m_loadThreadSetupComplete) {}
	}

	int getFrameCount() { return m_currentFrameCount; }

	void setPauseAnimation(bool pause) { m_pauseAnimation = pause; }

	void loadAnimation(Animation animation) { loadAnimations({ animation }); }
	void loadAnimations(std::vector<Animation> animations)
	{
		for (Animation animation : animations)
			pushJob({AnimationJobType::LOAD, animation });
		
	}

	void unloadAnimation(Animation animation) { unloadAnimations({ animation }); }
	void unloadAnimations(std::vector<Animation> animations)
	{
		for (Animation animation : animations)
			pushJob({ AnimationJobType::UNLOAD, animation });

	}

	void startup(Animation animation, bool loopAnimation = false)
	{
		m_currentAnimation = animation;
		m_currentFrameCount = 0;

		m_countTarget = 1.0f / (float)m_animations[animation].fps;
		m_count = m_countTarget;

		m_loop = loopAnimation;

		m_stopAnimation = false;
		cv.notify_all();

		while (!animationLoaded(animation) && !shouldClose()) { updateRenderer(); }

		m_animationFrames = &m_loadedAnimations[animation];
	};

	void stream(bool callUpdateRenderer = true)
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
			m_renderer->renderTexture(&m_animationFrames->at(m_currentFrameCount));

			if (!m_pauseAnimation)
			{
				m_currentFrameCount++;
				m_count = 0.0f;
			}
		}
		else
		{
			m_renderer->renderTexture(&m_animationFrames->at(m_currentFrameCount));

			if (!m_pauseAnimation)
				m_count += m_timer->getDelta();
		}

		if (callUpdateRenderer)
			updateRenderer();

	}

	void updateRenderer() { m_renderer->onUpdate(); };

	bool animationPlaying() { return m_currentFrameCount < m_animations[m_currentAnimation].frameCount; }

	bool animationLoaded(Animation animation)
	{
		if (m_loadedAnimations.count(animation) == 0)
			return false;

		if (m_loadedAnimations[animation].size() != m_animations[animation].frameCount)
			return false;

		return true;
	}

private:

	void setupContext()
	{
		glfwMakeContextCurrent(m_renderer->getSharedWindow());
		glewInit();

		GLenum returnCode = glewInit();

		if (returnCode != GLEW_OK)
		{
			std::cout << "[ANIMATOR] Return Code Error: " << returnCode << std::endl;
			glfwMakeContextCurrent(NULL);
			exit(returnCode);
		}
	}

	void shutdownContext()
	{
		m_loadingComplete = true;

		glfwMakeContextCurrent(NULL);
	}

	bool shouldClose()
	{
		return glfwWindowShouldClose(m_renderer->getSharedWindow()) || glfwWindowShouldClose(m_renderer->getWindow()) || m_stopAnimation;
	}

	bool shouldHandleJob()
	{
		m_semaphore.wait();

		m_loadingComplete = false;

		if (frontJob().animation == Animation::STREAM_END)
			return false;

		return true;
	}

	void loadAnimationFrames()
	{

		Animation animation = frontJob().animation;

		std::string path = m_animationDir + m_animations[animation].name + "/" + m_animations[animation].name + "_";

		m_loadedAnimations[animation] = std::vector<Texture>();

		for (int i = 0; i < m_animations[animation].frameCount; i++)
		{
			if (shouldClose())
				return;

			std::string animationPath = path + std::to_string(i) + ".png";
			m_loadedAnimations[animation].push_back(Texture(animationPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE));
		}

	}

	void unloadAnimationFrames()
	{
		Animation animation = frontJob().animation;

		for (int i = 0; i < m_animations[animation].frameCount; i++)
		{
			if (shouldClose())
				return;

			m_loadedAnimations[animation].at(0).Delete();
			m_loadedAnimations[animation].erase(m_loadedAnimations[animation].begin());
		}

		m_loadedAnimations.erase(animation);
	}

	void handleJob()
	{
		//TODO: Determine if the job should be completed
		// IE. Check if the Animation is already loaded before loading.
		// IE. Check if the animation is loaded before unloading

		if (frontJob().type == AnimationJobType::LOAD)
			loadAnimationFrames();
		else
			unloadAnimationFrames();

		popJob();
	}

	void animationJobThread()
	{
		m_loadThreadSetupComplete = true;
		while (true)
		{
			if (!shouldHandleJob())
				break;

			setupContext();

			handleJob();

			shutdownContext();
		}
	}

	AnimationJob frontJob()
	{
		std::lock_guard<std::mutex> guard(streamLock);

		return m_streamThreadJobs.front();
	}

	void pushJob(AnimationJob animation)
	{
		std::lock_guard<std::mutex> guard(streamLock);
		m_streamThreadJobs.push(animation);
		m_semaphore.signal();
	}

	void popJob()
	{
		std::lock_guard<std::mutex> guard(streamLock);

		m_streamThreadJobs.pop();
	}

private:
	Renderer* m_renderer = nullptr;
	Timer* m_timer = nullptr;
	std::string m_animationDir = "Animations/";

private:
	Animation m_currentAnimation = Animation::NONE;

	std::vector<Texture>* m_animationFrames = nullptr;
	int m_currentFrameCount = 0;
	float m_count = 0.0f;
	float m_countTarget = 0.0f;

	bool m_loadingComplete = true;
	bool m_unloadingComplete = true;
	bool m_loop = false;
	bool m_pauseAnimation = false;
	bool m_stopAnimation = false;


private:
	bool m_loadThreadSetupComplete = false;

	std::thread m_loadThread;
	std::queue<AnimationJob> m_streamThreadJobs;

	std::mutex streamLock;
	std::condition_variable cv;

	Semaphore m_semaphore;

private:
	

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
		{Animation::GRASS_ENCOUNTER,	{"grassEncounter",		81,		60}},
	};

	std::unordered_map<Animation, std::vector<Texture>> m_loadedAnimations{};
};


class AnimationQueue
{
public:

	AnimationQueue() {};

	int size();
	bool empty();
	void clear();

	bool shift();

	Texture* getCurrentTexture();

	void addTexture(Texture* texture);

private:

	std::queue<Texture*> m_textures;
	Texture* m_currentTexture = nullptr;

	std::mutex m_queueLock;
};

class AnimationStream
{
public:
	AnimationStream() {};
	AnimationStream(Renderer* renderer, Timer* timer);
	~AnimationStream();

	void setup(Renderer* renderer, Timer* timer);

	void setAnimation(Animation anim, bool loopAnimation = false);
	void stopAnimation();

	int getFrameCount();

	bool animationReady();
	bool animationPlaying();

	void stream(bool callRendererUpdate = false);

	void updateRenderer();

private:

	void queueThread();
	void makeFrame(int count);

	void setupRenderContext();
	void shutdownRenderContext();

private:
	AnimationQueue m_animationQueue;

	Renderer* m_renderer = nullptr;
	Timer* m_timer = nullptr;

	std::thread m_queueThread;
	std::mutex m_streamLock;
	Semaphore m_semaphore;

private:
	Animation m_currentAnimation = Animation::NONE;
	AnimationData m_animationData;

	bool m_loopAnimation = false;
	bool m_stopLoading = false;
	bool m_threadStopped = false;
	bool m_joinThread = false;

	int m_frameCount = 0;
	int m_maxFrameCount = 0;

	float m_currentFrameDelta = 0.0f;
	float m_frameDeltaTarget = 0.0f;

	bool m_setupComplete = false;
};