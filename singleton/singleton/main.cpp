#include <vector>
#include <thread>

#include "Singleton.h"

void task()
{
	Singleton& single = get_Singleton();
	std::cout << &single << std::endl;
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(task));

	for (auto& t : threads)
		t.join();
}
