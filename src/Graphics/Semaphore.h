#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
	Semaphore() {};
	Semaphore(int count) { m_counter = count; }

	void signal()
	{
		{
			std::lock_guard<std::mutex> guard(m_counterLock);
			m_counter++;
		}

		m_cv.notify_all();
	}

	void wait()
	{
		std::unique_lock<std::mutex> guard(m_counterLock);
		m_cv.wait(guard, [this] {return m_counter > 0; });
		m_counter--;
	}

private:
	mutable std::mutex m_counterLock;
	std::condition_variable m_cv;
	unsigned int m_counter = 0;
};