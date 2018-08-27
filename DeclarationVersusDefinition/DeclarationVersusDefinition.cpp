// DeclarationVersusDefinition.cpp
// Created 8/23/2018 10:49:12 PM

#include <iostream>

#include "func.h"
#include "A.h"
#include "B.h"

int main() {
	std::cout << "Calling twice in main with 3: " << twice(3) << '\n';
	std::cout << "Calling a in main: ";
	a();
	b();
	std::cout << '\n';
	
}
