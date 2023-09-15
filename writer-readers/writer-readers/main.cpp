#include <mutex>
#include <shared_mutex>
#include <vector>

std::shared_mutex shmut;
int x = 0; // shared data

void write()
{
	// exclusive lock
	std::unique_lock lg(shmut);

	// start of critical section
	++x;
	// end of critical section
}

void read()
{
	std::shared_lock sl(shmut);

	// start of critical section
	using namespace std::literals;
	std::this_thread::sleep_for(100ms);
	// end of critical section
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	threads.push_back(std::thread(write));
	threads.push_back(std::thread(write));

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	for (auto& t : threads)
		t.join();
}
