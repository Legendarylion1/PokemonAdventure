#include "PokedexRingBuffer.h"

void PokedexRingBuffer::init()
{
	BufferElement* element0 = new BufferElement();
	BufferElement* element1 = new BufferElement();
	BufferElement* element2 = new BufferElement();
	BufferElement* element3 = new BufferElement();
	BufferElement* element4 = new BufferElement();
	BufferElement* element5 = new BufferElement();
	BufferElement* element6 = new BufferElement();

	element0->up = element6;
	element0->down = element1;

	element1->up = element0;
	element1->down = element2;

	element2->up = element1;
	element2->down = element3;

	element3->up = element2;
	element3->down = element4;

	element4->up = element3;
	element4->down = element5;

	element5->up = element4;
	element5->down = element6;

	element6->up = element5;
	element6->down = element0;

	element3->index = 0;
	element0->index = 1;
	element1->index = 2;
	element2->index = 3;
	element4->index = 4;
	element5->index = 5;
	element6->index = 6;

	m_bufferElements.push_back(element3);
	m_bufferElements.push_back(element0);
	m_bufferElements.push_back(element1);
	m_bufferElements.push_back(element2);
	m_bufferElements.push_back(element4);
	m_bufferElements.push_back(element5);
	m_bufferElements.push_back(element6);
}

void PokedexRingBuffer::reset()
{
	m_currentBufferElementIndex = 0;
}

void PokedexRingBuffer::rotateUp()
{

	m_currentBufferElementIndex = m_bufferElements.at(m_currentBufferElementIndex)->up->index;
	//if (m_currentBufferElementIndex == 0)
	//	m_currentBufferElementIndex = m_bufferElements.size() - 1;
	//else
	//	m_currentBufferElementIndex--;
}

void PokedexRingBuffer::rotateDown()
{
	m_currentBufferElementIndex = m_bufferElements.at(m_currentBufferElementIndex)->down->index;
	//if (m_currentBufferElementIndex == m_bufferElements.size() - 1)
	//	m_currentBufferElementIndex = 0;
	//else
	//	m_currentBufferElementIndex++;
}

std::vector<int> PokedexRingBuffer::getIndexOrder()
{
	std::vector<int> order;

	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->up->up->up->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->up->up->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->up->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->down->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->down->down->index);
	order.push_back(m_bufferElements.at(m_currentBufferElementIndex)->down->down->down->index);

	return order;
}
