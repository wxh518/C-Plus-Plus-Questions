#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int g_Num;
mutex g_Mutex;
condition_variable g_Cv;
int g_Turn[3] = {0};

void func()
{
	while (g_Num < 100)
	{
		std::unique_lock<std::mutex> locker(g_Mutex);
		//g_Mutex.lock();
		std::cout << std::this_thread::get_id() << "->" << g_Num++ << std::endl;
		//g_Mutex.unlock();
	}
}

void func1()
{
	while (g_Num < 100)
	{
		std::unique_lock<std::mutex> locker(g_Mutex);
		g_Cv.wait(locker, []()
			{
				return g_Turn[0];
			});
		std::cout << std::this_thread::get_id() << "->" << g_Num++ << std::endl;
		g_Turn[0] = false;
		g_Turn[1] = true;
		g_Turn[2] = false;
		g_Cv.notify_all();
	}
}

void func2()
{
	while (g_Num < 100)
	{
		std::unique_lock<std::mutex> locker(g_Mutex);
		g_Cv.wait(locker, []()
			{
				return g_Turn[1];
			});
		std::cout << std::this_thread::get_id() << "->" << g_Num++ << std::endl;
		g_Turn[0] = false;
		g_Turn[1] = false;
		g_Turn[2] = true;
		g_Cv.notify_all();
	}
}

void func3()
{
	while (g_Num < 100)
	{
		std::unique_lock<std::mutex> locker(g_Mutex);
		g_Cv.wait(locker, []()
			{
				return g_Turn[2];
			});
		std::cout << std::this_thread::get_id() << "->" << g_Num++ << std::endl;
		g_Turn[0] = true;
		g_Turn[1] = false;
		g_Turn[2] = false;
		g_Cv.notify_all();
	}
}

int main()
{
	std::cout << "Hello World!" << std::endl;

	g_Turn[0] = 1;

	std::thread t1(func1);
	std::thread t2(&func2);
	std::thread t3(&func3);

	t1.join();
	t2.join();
	t3.join();

	cin.get();
	return 0;
}