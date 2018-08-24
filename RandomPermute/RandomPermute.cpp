// RandomPermute.cpp
// Created 8/23/2018 10:18:47 PM

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

//  Returns a pseudorandom number in the range begin...end - 1
int random(int begin, int end) {
	if (begin >= end)
		return 0;
	else {
		int range = end - begin;
		return begin + rand() % range;
	}
}



// Randomly permute a vector
void permute1(std::vector<int>& a) {
	int n = a.size();
	for (int i = 0; i < n - 1; i++) {
		// Select a pseudorandom location from the current
		// location to the end of the collection
		std::swap(a[i], a[random(i, n)]);
	}
}

// Randomly permute a vector?
void permute2(std::vector<int>& a) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		// Select a pseudorandom position somewhere in the collection
		std::swap(a[i], a[random(0, n)]);
	}
}

// Classify a vector as one of the six permutations
int classify(const std::vector<int>& a) {
	switch (100 * a[0] + 10 * a[1] + a[2]) {
		case 123:  return 0;
		case 132:  return 1;
		case 213:  return 2;
		case 231:  return 3;
		case 312:  return 4;
		case 321:  return 5;
	}
	return -1;
}

// Report the accumulated statistics
void report(const std::vector<int>& a) {
	std::cout << "1,2,3: " << a[0] << '\n';
	std::cout << "1,3,2: " << a[1] << '\n';
	std::cout << "2,1,3: " << a[2] << '\n';
	std::cout << "2,3,1: " << a[3] << '\n';
	std::cout << "3,1,2: " << a[4] << '\n';
	std::cout << "3,2,1: " << a[5] << '\n';
}

// Fill the given vector with zeros
void clear(std::vector<int>& a) {
	for (auto iter = a.begin(); iter != a.end(); iter++)
		*iter = 0;
}

int main() {
	// Initialize random generator seed
	srand(static_cast<int>(time(0)));

	// permutation_tally vector keeps track of each permutation pattern
	// permutation_tally[0] counts number of occurrences of {1,2,3}
	// permutation_tally[1] counts number of occurrences of {1,3,2}
	// permutation_tally[2] counts number of occurrences of {2,1,3}
	// permutation_tally[3] counts number of occurrences of {2,3,1}
	// permutation_tally[4] counts number of occurrences of {3,1,2}
	// permutation_tally[5] counts number of occurrences of {3,2,1}
	std::vector<int> permutation_tally {0, 0, 0, 0, 0, 0};  // Zero all counters

	// original always holds the vector {1,2,3}
	const std::vector<int> original {1, 2, 3};

	// working holds a copy of original is gets permuted and tallied
	std::vector<int> working;

	// Print the original vector
	for_each(original.begin(), original.end(),
		[](int x) { std::cout << x << ' '; });
	std::cout << '\n';

	// Run each permutation one million times
	const int RUNS = 1'000'000;

	std::cout << "--- Random permute #1 -----" << '\n';
	clear(permutation_tally);
	for (int i = 0; i < RUNS; i++) {  // Run 1,000,000 times
		// Make a copy of the original vector
		working = original;
		// Permute the vector with the first algorithm
		permute1(working);
		// Count this permutation
		permutation_tally[classify(working)]++;
	}
	report(permutation_tally);   // Report results

	std::cout << "--- Random permute #2 -----" << '\n';
	clear(permutation_tally);
	for (int i = 0; i < RUNS; i++) {  // Run 1,000,000 times
		// Make a copy of the original vector
		working = original;
		// Permute the vector with the second algorithm
		permute2(working);
		// Count this permutation
		permutation_tally[classify(working)]++;
	}
	report(permutation_tally);   // Report results
}


