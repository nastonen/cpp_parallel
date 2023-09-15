#include <thread>
#include <mutex>
#include <iostream>

class Test
{
public:
	Test()
	{
		std::cout << "Test constructor called\n";
	}

	void func()
	{
		std::cout << "func() called\n";
	}
};

//Test* ptest = nullptr;
//std::once_flag ptest_flag;

void process()
{
	// Use call_once for ensuring 'ptest' will be inited only once
	/*std::call_once(ptest_flag, []() {
		ptest = new Test;
	});*/

	// or use Meyers singleton (preferred)
	static Test ptest; // will be lazily initialized

	ptest.func();
}

int main()
{
	std::thread t1(process);
	std::thread t2(process);
	t1.join();
	t2.join();
}
