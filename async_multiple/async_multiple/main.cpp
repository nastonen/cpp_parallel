#include <future>
#include <iostream>
#include <chrono>

int calc(const int n)
{
	using namespace std::literals;
	std::this_thread::sleep_for(std::chrono::seconds(n));

	return n;
}

int main()
{
	auto r1 = std::async(std::launch::async, calc, 5);
	auto r2 = std::async(std::launch::async, calc, 2);
	auto r3 = std::async(std::launch::async, calc, 3);

	//r1.wait();
	std::cout << "Waiting for r1..." << std::endl;

	//r2.wait();
	std::cout << "Waiting for r2..." << std::endl;

	//r3.wait();
	std::cout << "Waiting for r3..." << std::endl;

	
	// The calls are blocking. Will wait for 5s.
	std::cout << "r1: " << r1.get() << std::endl;
	std::cout << "r2: " << r2.get() << std::endl;
	std::cout << "r3: " << r3.get() << std::endl;
}
