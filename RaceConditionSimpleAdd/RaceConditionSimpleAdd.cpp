
#include <iostream>
#include <thread>
#include <chrono>

// Global counter variable
unsigned long count = 0;

void count_up(int n) {
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	for (int i = 0; i < n; i++) {
		count++;
	}
}

void check_it() {
	count = 0; // Reset global counter variable to zero
	const int ITERATIONS = 100'000'000;
	std::thread t1{ count_up, ITERATIONS };
	std::thread t2{ count_up, ITERATIONS };
	std::thread t3{ count_up, ITERATIONS };
	std::thread t4{ count_up, ITERATIONS };
	std::thread t5{ count_up, ITERATIONS };
	//count_up(10'000'000);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	std::cout << "count = " << count << '\n';
}

int main() {
	for (int i = 0; i < 5; i++) {
		check_it();
	}
}
