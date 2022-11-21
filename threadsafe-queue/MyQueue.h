#pragma once
#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>

struct Log
{
	int id;
	std::string info;
};

class MyQueue
{
public:
	MyQueue(int maxSize);
	~MyQueue();

	void Push(const Log& log);
	Log Pop();

private:
	std::deque<Log> m_Queue;
	std::mutex m_Mutex;
	std::condition_variable m_NotFull;
	std::condition_variable m_NotEmpty;
	int m_MaxSize;
};