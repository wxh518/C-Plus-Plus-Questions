#pragma once
#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <iostream>

template<typename T>
class MyQueue2
{
public: 
	MyQueue2(int maxSize) : m_MaxSize(maxSize)
	{
		m_Queue.clear();
		std::cout << "m_MaxSize: " << m_MaxSize << std::endl;
	}
	~MyQueue2()
	{
		m_Queue.clear();
	}

	void Push(const T& t)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);
		m_NotFull.wait(locker, [this]()
			{
				return m_Queue.size() < m_MaxSize;
			});
		m_Queue.push_back(std::move(t));
		std::cout << __FUNCTION__ << " " << t << " m_Queue.size(): " << m_Queue.size() << std::endl;
		m_NotEmpty.notify_all();
	}
	T Pop()
	{
		std::unique_lock<std::mutex> locker(m_Mutex);
		m_NotEmpty.wait(locker, [this]()
			{
				return !m_Queue.empty();
			});
		T t = m_Queue.front();
		m_Queue.pop_front();
		m_NotFull.notify_all();
		std::cout << __FUNCTION__ << " " << t << " m_Queue.size(): " << m_Queue.size() << std::endl;
		return t;
	}

private:
	std::deque<T> m_Queue;
	std::mutex m_Mutex;
	std::condition_variable m_NotFull;
	std::condition_variable m_NotEmpty;
	int m_MaxSize;
};