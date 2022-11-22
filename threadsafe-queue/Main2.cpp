#include <iostream>
#include <thread>
#include <chrono>

#include "MyQueue.h"
#include "MyQueue2.h"

using namespace std;

struct MyLog
{
	int id;
	std::string info;

	friend std::ostream& operator << (std::ostream& os, const MyLog& rhs)
	{
		os << "id: " << rhs.id << " info: " << rhs.info << std::endl;
		return os; 
	}
};

MyQueue2<MyLog> q(5);
int g_logid;
std::mutex g_Mutex;
bool g_Quit;

void func1()
{
	while (!g_Quit)
	{
		MyLog log;
		{
			std::unique_lock<std::mutex> locker(g_Mutex);
			log.id = g_logid;
			log.info = std::to_string(g_logid);
			g_logid++;
			//std::cout << __FUNCTION__ << " " << log << std::endl;
		}

		q.Push(log);
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func2()
{
	while (!g_Quit)
	{
		MyLog log = q.Pop();
		//std::cout << __FUNCTION__ << " " << log << std::endl;
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func3()
{
	while (!g_Quit)
	{
		MyLog log;
		{
			std::unique_lock<std::mutex> locker(g_Mutex);
			log.id = g_logid;
			log.info = std::to_string(g_logid);
			g_logid++;
			//std::cout << __FUNCTION__ << " " << log << std::endl;
		}

		q.Push(log);
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func4()
{
	while (!g_Quit)
	{
		MyLog log = q.Pop();
		//std::cout << __FUNCTION__ << " " << log << std::endl;
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

int main()
{
	std::cout << "Hello World!" << std::endl;

	std::thread t1(func1);
	std::thread t2(func2);
	//std::thread t3(func3);
	std::thread t4(func4);
	t1.join();
	t2.join();
	//t3.join();
	t4.join();

	std::cin.get();
	return 0;
}