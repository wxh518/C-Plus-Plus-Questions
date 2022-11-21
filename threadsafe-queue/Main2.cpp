#include <iostream>
#include <thread>
#include <chrono>

#include "MyQueue.h"

using namespace std;

MyQueue q(5);
int g_logid;
std::mutex g_Mutex;
std::condition_variable g_Cv;
bool g_Quit;
int turn[2] = { 1, 0 };

void func1()
{
	while (!g_Quit)
	{
		Log log;
		{
			std::unique_lock<std::mutex> locker(g_Mutex);
			log.id = g_logid;
			log.info = std::to_string(g_logid);
			g_logid++;
			//std::cout << __FUNCTION__ << " " << log.id << "->" << log.info << std::endl;
		}

		q.Push(log);
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func2()
{
	while (!g_Quit)
	{
		Log log = q.Pop();
		//std::cout << __FUNCTION__ << " " << log.id << "->" << log.info << std::endl;
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func3()
{
	while (!g_Quit)
	{
		Log log;
		{
			std::unique_lock<std::mutex> locker(g_Mutex);
			log.id = g_logid;
			log.info = std::to_string(g_logid);
			g_logid++;
			//std::cout << __FUNCTION__ << " " << log.id << "->" << log.info << std::endl;
		}

		q.Push(log);
		this_thread::sleep_for(chrono::seconds(1)); //ÐÝÃß1s
	}
}

void func4()
{
	while (!g_Quit)
	{
		Log log = q.Pop();
		//std::cout << __FUNCTION__ << " " << log.id << "->" << log.info << std::endl;
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