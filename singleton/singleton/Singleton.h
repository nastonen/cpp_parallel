#pragma once

#include <iostream>

class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	Singleton()
	{
		std::cout << "Initializing singleton\n";
	}
};

Singleton& get_Singleton()
{
	static Singleton single;
	return single;
}
