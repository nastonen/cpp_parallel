#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

using namespace std::literals;

constexpr int nforks = 5;
constexpr int nphils = nforks;
std::string names[nphils] = { "A", "B", "C", "D", "E" };

// Keep track of how many time a phil was able to eat
int mouthfuls[nphils] = { 0 };

constexpr auto think_time = 2s;
constexpr auto eat_time = 1s;

std::mutex fork_mutex[nforks];
std::mutex print_mutex;

// Interactions with forks
void print(int n, const std::string& str, int lfork, int rfork)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str;
	std::cout << lfork << " and " << rfork << '\n';
}

// The philosopher's state
void print(int n, const std::string& str)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str << '\n';
}

void dine(int phil_no)
{
	int lfork = phil_no;
	int rfork = (phil_no + 1) % nforks;

	print(phil_no, "\'s forks are ", lfork, rfork);
	print(phil_no, " is thinking...");

	std::this_thread::sleep_for(think_time);

	// Make an attempt to eat
	print(phil_no, " reaches for forks ", lfork, rfork);

	// Try to lock up both forks
	std::scoped_lock lock(fork_mutex[lfork], fork_mutex[rfork]);
	print(phil_no, " picks up fork ", lfork, rfork);

	// Succeeded - this philosopher can now eat
	print(phil_no, " is eating...");
	++mouthfuls[phil_no];

	std::this_thread::sleep_for(eat_time);

	print(phil_no, " puts down fork ", lfork, rfork);
	print(phil_no, " is thinking...");

	std::this_thread::sleep_for(think_time);
}

int main()
{
	// Start a separate thread for each philosopher
	std::vector<std::thread> phils;

	for (int i = 0; i < nphils; ++i)
		phils.push_back(std::move(std::thread{ dine, i }));

	for (auto& phil : phils)
		phil.join();

	// How many times were the philosophers able to eat?
	for (int i = 0; i < nphils; ++i) {
		std::cout << "Philosopher " << names[i];
		std::cout << " had " << mouthfuls[i] << " mouthful\n";
	}
}
