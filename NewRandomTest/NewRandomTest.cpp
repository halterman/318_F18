// NewRandomTest.cpp
// Created 8/29/2018 10:13:48 AM

#include <iostream> 
#include "uniformrandom.h" 

int main() {
	// r makes random integers
	auto r = UniformRandomGenerator(20, 30);
	int count = 0;
	for (int i = 0; i < 100; i++) {
		// Obtain a random integer from r
		int x = r();
		std::cout << x << '\n'; // Print the integer 
		count++;
	}
	std::cout << "count = " << count << '\n';
}
