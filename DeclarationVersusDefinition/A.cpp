#include <iostream>

#include "func.h"
#include "func2.h"

void a() {
	std::cout << "Inside the a function: " << twice(5) << '\n';
	std::cout << "Inside the a function: " << thrice(5) << '\n';
}