#include "MyQueue.h"
#include <iostream>

MyQueue::MyQueue(int maxSize) : m_MaxSize(maxSize)
{
	m_Queue.clear();
	//if (m_MaxSize > 0)
	//	m_Queue.resize(m_MaxSize);
	//else
	//	m_MaxSize = 10;
	std::cout << "m_MaxSize: " << m_MaxSize << std::endl;
}

MyQueue::~MyQueue()
{
	m_Queue.clear();
}

void MyQueue::Push(const Log& log)
{
	std::unique_lock<std::mutex> locker(m_Mutex);
	m_NotFull.wait(locker, [this]()
		{
			return m_Queue.size() < m_MaxSize;
		});
	m_Queue.push_back(std::move(log)); 
	std::cout << __FUNCTION__ << " " << log.id << " m_Queue.size(): " << m_Queue.size() << std::endl;
	m_NotEmpty.notify_all();
}

Log MyQueue::Pop()
{
	std::unique_lock<std::mutex> locker(m_Mutex);
	m_NotEmpty.wait(locker, [this]()
		{
			return !m_Queue.empty();
		});
	Log log = m_Queue.front();
	m_Queue.pop_front();
	m_NotFull.notify_all();
	std::cout << __FUNCTION__ << " " << log.id << " m_Queue.size(): " << m_Queue.size() << std::endl;
	return log;
}
