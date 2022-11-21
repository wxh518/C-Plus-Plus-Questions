#include <iostream>

#include "Singleton.h"
#include <memory>

using namespace std;

int main()
{
	std::cout << "Hello World!" << std::endl;

	{
		std::unique_ptr<Singleton> singleton = std::unique_ptr<Singleton>(Singleton::getInstance());
	}

	std::cin.get();
	return 0;
}