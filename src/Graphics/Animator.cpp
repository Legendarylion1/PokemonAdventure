#include "Animator.h"

AnimationStream::AnimationStream(Renderer* renderer, Timer* timer)
{
	setup(renderer, timer);
}

AnimationStream::~AnimationStream()
{
	m_joinThread = true;
	m_stopLoading = true;

	m_semaphore.signal();
	m_queueThread.join();
}

void AnimationStream::setup(Renderer* renderer, Timer* timer)
{
	m_renderer = renderer;
	m_timer = timer;

	m_queueThread = std::thread(&AnimationStream::queueThread, this);
}

void AnimationStream::setAnimation(Animation anim, bool loopAnimation)
{
	m_frameCount = 0;
	m_animationData = getAnimationData(anim);
	m_maxFrameCount = m_animationData.frameCount;
	m_currentAnimation = anim;
	m_frameDeltaTarget = 1.0f / (float)m_animationData.fps;
	m_currentFrameDelta = m_frameDeltaTarget + 1.0f;
	m_loopAnimation = loopAnimation;

	m_semaphore.signal();
}

void AnimationStream::stopAnimation()	//TODO: Ensure that this is called when done animating
{
	if (m_currentAnimation == Animation::NONE)
		return;

	m_stopLoading = true;

	while (!m_threadStopped) {}

	m_animationQueue.clear();
	m_loopAnimation = false;
	m_threadStopped = false;
	m_stopLoading = false;
	m_currentAnimation = Animation::NONE;
}

int AnimationStream::getFrameCount()
{
	return m_frameCount;
}

bool AnimationStream::animationReady()
{
	return m_animationQueue.size() < (1.0f/8.0f) * m_maxFrameCount;
}

bool AnimationStream::animationPlaying()
{
	if (m_loopAnimation)
		return true;

	if (m_frameCount < m_maxFrameCount)
		return true;

	if (m_currentFrameDelta < m_frameDeltaTarget)
		return true;

	return false;
}

void AnimationStream::stream(bool callRendererUpdate)
{
	if (m_currentFrameDelta > m_frameDeltaTarget)
	{
		if (m_animationQueue.shift())
		{
			m_frameCount++;
			m_currentFrameDelta = 0.0f;
		}
	}

	m_renderer->renderTexture(m_animationQueue.getCurrentTexture());

	m_currentFrameDelta += m_timer->getDelta();

	if (callRendererUpdate)
		updateRenderer();
}

void AnimationStream::updateRenderer()
{
	m_renderer->onUpdate();
}

void AnimationStream::queueThread()
{
	while (!m_joinThread)
	{
		m_semaphore.wait();

		int framesMade = 0;
		int maxQueueSize = (1.0f / 4.0f) * m_maxFrameCount;

		if (m_renderer->shouldClose())
		{
			m_threadStopped = true;
			continue;
		}

		setupRenderContext();
		while (framesMade < m_maxFrameCount && m_stopLoading == false && !m_renderer->shouldClose())
		{

			if (m_animationQueue.size() >= maxQueueSize)
				continue;		//TODO: Make this not a busy wait. Wait on CV or something

			makeFrame(framesMade);

			framesMade++;
		}
		shutdownRenderContext();

		if (m_loopAnimation && m_stopLoading == false && !m_renderer->shouldClose())
		{
			m_semaphore.signal();
		}
		else
		{
			m_threadStopped = true;
		}
	}
}

void AnimationStream::makeFrame(int count)
{
	//setupRenderContext();

	std::string m_animationDir = "Animations/";

	Animation animation = m_currentAnimation;

	std::string path = m_animationDir + m_animationData.name + "/" + m_animationData.name + "_";

	std::string animationPath = path + std::to_string(count) + ".png";
	m_animationQueue.addTexture(new Texture(animationPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE));
	
	//shutdownRenderContext();
}

void AnimationStream::setupRenderContext()
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

void AnimationStream::shutdownRenderContext()
{
	glfwMakeContextCurrent(NULL);
}

int AnimationQueue::size()
{
	return m_textures.size();
}

bool AnimationQueue::empty()
{
	return m_textures.empty();
}

void AnimationQueue::clear()
{
	std::lock_guard<std::mutex> guard(m_queueLock);

	if (m_currentTexture != nullptr)
	{
		m_currentTexture->Delete();
		delete m_currentTexture;

		m_currentTexture = nullptr;
	}

	while (m_textures.size() != 0)
	{
		m_currentTexture = m_textures.front();

		m_currentTexture->Delete();
		delete m_currentTexture;

		m_currentTexture = nullptr;

		m_textures.pop();
	}
}

bool AnimationQueue::shift()
{
	std::lock_guard<std::mutex> guard(m_queueLock);

	if (empty())
		return false;

	if (m_currentTexture != nullptr)
	{
		m_currentTexture->Delete();
		delete m_currentTexture;

		m_currentTexture = nullptr;
	}

	m_currentTexture = m_textures.front();
	m_textures.pop();

	return true;
}

Texture* AnimationQueue::getCurrentTexture()
{
	return m_currentTexture;
}

void AnimationQueue::addTexture(Texture* texture)
{
	std::lock_guard<std::mutex> guard(m_queueLock);

	m_textures.push(texture);
}
