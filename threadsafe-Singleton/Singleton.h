#pragma once
#include <mutex>

class Singleton
{
public:
	//Singleton* getInstance()
	//{
	//	//¶öººÄ£Ê½
	//	static Singleton instance;
	//	return &instance;
	//}

	static Singleton* getInstance();
	~Singleton();

private:
	Singleton();
	Singleton(const Singleton& rhs) = delete;
	Singleton& operator = (const Singleton& rhs) = delete;

	static Singleton* s_instance;
	static std::mutex s_Mutex;
};