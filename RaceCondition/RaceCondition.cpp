// RaceCondition.cpp
// Created 12/4/2018 10:01:17 PM

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdlib>

class Counter {
protected:
	unsigned long count;
public:
	Counter() : count(0) {}
	virtual void increment() {
		count++;
	}
	virtual unsigned int get() const {
		return count;
	}
	virtual void reset() {
		count = 0;
	}
};

// Global counter object
Counter ctr;

void count_up(int n) {
	for (int i = 0; i < n; i++) {
		ctr.increment();
	}
}

void check_it() {
	ctr.reset();   // Reset global counter object to zero
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
	std::cout << "ctr = " << ctr.get() << '\n';
}

int main() {
	for (int i = 0; i < 5; i++) {
		check_it();
	}
}
