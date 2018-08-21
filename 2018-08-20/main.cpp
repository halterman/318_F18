// Source code for main.cpp in the first CPTR 318 assignment

#include <iostream>
#include <vector>
#include <string>
#include "readfile.h"

int main() {
    std::vector v = read_file("words.txt");
    for (auto s : v)
        std::cout << s << '\n';
} 
