#include <thread>
#include "Vector.h"

void func(Vector& vec)
{
	for (int i = 0; i < 50; ++i) {
		vec.push_back(i);
		std::this_thread::sleep_for(50ms);
		vec.print();
	}
}

/**
  * chrono::system_clock is for OS clock which can jump around
  * chrono::steady_clock is for measuring intervals, always increases steadily
 */
int main()
{
	Vector v;

	std::thread t1(func, std::ref(v));
	std::thread t2(func, std::ref(v));
	std::thread t3(func, std::ref(v));

	t1.join();
	t2.join();
	t3.join();
}
