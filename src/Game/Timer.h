#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

class Timer
{
public:

	void resetTimer(){ m_lastTime = (float)glfwGetTime(); };

	float getDelta() 
	{
		return m_deltaTime; 
	};

	void countPlay(bool value) { m_countPlay = value; };

	void onUpdate()
	{
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (!m_countPlay)
			return;

		m_playCount += m_deltaTime;

		if (m_playCount < 60.0f)
			return;
		
		int increase = (int)floor(m_playCount / 60.0f);

		m_playTime += increase;
		m_playCount -= increase * 60.0f;
	};

	void setPlayTime(int playTime) { 
		float m_playCount = 0.0f;
		m_playTime = playTime;
	};

	std::string getPlayTimeDisplay() { return formatTime(m_playTime); };

	std::string formatTime(int time)
	{
		int hours = (int)floor(time / 60.0f);

		int minutes = time - (hours * 60);

		std::string data;

		if (hours < 10)
			data += "0";

		data += std::to_string(hours) + ":";

		if (minutes < 10)
			data += "0";

		data += std::to_string(minutes);

		return data;
	};
	

	int getPlayTime() { return m_playTime; };

	
private:

	int m_playTime = 0;
	float m_playCount = 0.0f;
	bool m_countPlay = false;

	float m_deltaTime = 0.0f;
	float m_lastTime = 0.0f;
};