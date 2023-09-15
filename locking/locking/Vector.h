#pragma once

#include <mutex>
#include <vector>
#include <iostream>

using namespace std::literals;

class Vector
{
private:
	std::timed_mutex m; // supports try_lock_for() and try_lock_until(), normal mutex does not
	std::vector<int> vec;

public:
	/**
	* Mutex lock()/unlock() never used.
	* Use lock_guard to lock a mutex for an entire scope.
	* Use unique_lock if you need to unlock within scope. (is slightly slower)
	* Use unique_lock if you need the extra features.
	* 
	* Use scoped_lock to acquire multiple mutexes to avoid deadlocks.
	*/
	void push_back(const int& i)
	{
		//m.lock();
		//std::lock_guard g(m);

		// If unlock() not called explicitly, destructor will call it.
		// defer_lock is passed because we don't want to lock on ctor, but later on
		std::unique_lock ul(m, std::defer_lock);
		if (!ul.try_lock_for(500ms)) {
			std::cout << "couldn't acquire lock" << std::endl;
			return;
		}
		vec.push_back(i);
		std::this_thread::sleep_for(1s);
		ul.unlock(); // if unlock() not called explicitly, destructor will call it

		//m.unlock();
	}

	void print()
	{
		//m.lock();

		//std::lock_guard g(m);

		std::unique_lock ul(m); // if unlock() not called explicitly, destructor will call it

		for (auto& i : vec)
			std::cout << i << ", ";
		std::cout << std::endl;
		
		ul.unlock(); // if unlock() not called explicitly, destructor will call it

		//m.unlock();
	}
};
