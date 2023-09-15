#include <iostream>
#include <thread>
#include <sstream>

using namespace std::literals;

void foo(std::string&& str)
{
	std::this_thread::sleep_for(2s);

	std::stringstream stream;
	stream << str << "hello from foo() - " << std::this_thread::get_id() << std::endl;
	std::cout << stream.str();
}

void foo1(const std::string& str)
{
	std::stringstream stream;
	stream << str << " hello from foo() - " << std::this_thread::get_id() << std::endl;
	std::cout << stream.str();
}

class my_class
{
public:
	void operator()()
	{
		std::stringstream stream;
		stream << "Hello from class - " << std::this_thread::get_id() << std::endl;
		std::cout << stream.str();
	}
};

class my_class1
{
public:
	void hello()
	{
		std::stringstream stream;
		stream << "Hello from class function - " << std::this_thread::get_id() << std::endl;
		std::cout << stream.str();
	}
};

void a()
{
	std::stringstream stream;
	stream << "Hello from a function - " << std::this_thread::get_id() << std::endl;
	std::cout << stream.str();
}

int main()
{
	/*
	// we can call a function in a thread
	// here ownership of 'str' is transferred to foo()
	std::string str = "Movable ";
	std::thread t1(foo, std::move(str)); // set up a thread with function foo()

	// this is how to pass by (constant) reference
	// be sure that the string lives as long as thread runs!
	std::string str1 = "Reference ";
	std::thread t11(foo1, std::cref(str1));

	// or a class with 'operator()' public method
	my_class obj;
	std::thread t2(obj);

	// or just a member function of the class
	my_class1 obj1;
	std::thread t22(&my_class1::hello, &obj1);

	// or a lambda (with caption)
	int i = 3;
	std::thread t3([&i] {
		std::stringstream stream;
		stream << "Hello from lambda " << "i: " << i * 3 << "; - " << std::this_thread::get_id() << std::endl;
		std::cout << stream.str();
	});

	if (t1.joinable())
		t1.join(); // start execution
	if (t11.joinable())
		t11.join();
	if (t2.joinable())
		t2.join();
	if (t22.joinable())
		t22.join();
	if (t3.joinable())
		t3.join();
	*/

	//std::jthread jt1(foo1, "asdf");
	//std::cout << "starting thread" << std::endl;
	//jt1.get_id();

	std::cout << "There are " << std::thread::hardware_concurrency() << " hardware threads on this system." << std::endl;
}
