#include <random>
#include <thread>
#include <iostream>

// each thread will have it's own copy of this
thread_local std::mt19937 mt;

void func()
{
	std::uniform_real_distribution<double> dist(0, 1);

	for (int i = 0; i < 10; ++i)
		std::cout << dist(mt) << ", ";
}

int main()
{
	std::cout << "Thread 1's random values:\n";
	std::thread t1(func);
	t1.join();

	std::cout << "Thread 2's random values:\n";
	std::thread t2(func);
	t2.join();
}
