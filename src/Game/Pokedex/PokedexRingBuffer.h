#pragma once

#include <vector>

class PokedexRingBuffer
{
public:
	PokedexRingBuffer() {};

	void init();
	void reset();

	void rotateUp();
	void rotateDown();

	int getAboveCenterIndex() { return m_bufferElements.at(m_currentBufferElementIndex)->up->index; };
	int getCenterIndex() { return m_bufferElements.at(m_currentBufferElementIndex)->index; };
	int getBelowCenterIndex() { return m_bufferElements.at(m_currentBufferElementIndex)->down->index; };

	std::vector<int> getIndexOrder();
private:

	struct BufferElement
	{
		BufferElement* up;
		BufferElement* down;
		int index;
	};

	std::vector<BufferElement*> m_bufferElements;
	int m_currentBufferElementIndex = 3;
};