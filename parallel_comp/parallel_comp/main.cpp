#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <future>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double* start, double* end)
{
	return std::accumulate(start, end, 0.0);
}

// Divide the data into 4 parts
// Use a separate part to process each subset
double add_parallel(std::vector<double>& vec)
{
	// Find the first element of the vector
	auto vec0 = &vec[0];

	// Find the number of elements
	auto vsize = vec.size();

	// Start the threads
	// Pass the subset's range as argument to the task function
	auto f1 = std::async(std::launch::async, accum, vec0, vec0 + vsize / 4);
	auto f2 = std::async(std::launch::async, accum, vec0 + 1 * vsize / 4, vec0 + 2 * vsize / 4);
	auto f3 = std::async(std::launch::async, accum, vec0 + 2 * vsize / 4, vec0 + 3 * vsize / 4);
	auto f4 = std::async(std::launch::async, accum, vec0 + 3 * vsize / 4, vec0 + vsize);

	// Reduce step
	// Combine the results for each subset
	return f1.get() + f2.get() + f3.get() + f4.get();
}

int main()
{
	// Populate a vector with elements 1, 2, ..., 16
	std::vector<double> vec(16);
	std::iota(vec.begin(), vec.end(), 1.0);

	// Populate a vector with 10,000 random elements
	std::vector<double> vrand(10'000);
	std::generate(vrand.begin(), vrand.end(), [&vrand]() { return dist(mt); });

	// Do the calculations
	std::cout << "Sum of first 16 integers: " << add_parallel(vec) << std::endl;
	std::cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << std::endl;
}
