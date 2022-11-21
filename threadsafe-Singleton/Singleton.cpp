#include "Singleton.h"
#include <iostream>

Singleton* Singleton::getInstance()
{
	if (!Singleton::s_instance)
	{
		std::lock_guard<std::mutex> locker(s_Mutex);
		if (!Singleton::s_instance)
		{
			Singleton::s_instance = new Singleton();
		}
	}
	return Singleton::s_instance;
}

Singleton::Singleton()
{
	std::cout << __FUNCTION__ << " " << "init singleton..." << std::endl;
}

Singleton* Singleton::s_instance = nullptr;
std::mutex Singleton::s_Mutex;

Singleton::~Singleton()
{
	std::cout << __FUNCTION__ << " " << "shut down singleton..." << std::endl;
}
