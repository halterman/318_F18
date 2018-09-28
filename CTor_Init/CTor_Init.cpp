// CTor_Init.cpp
// Created 9/27/2018 10:45:25 AM

#include <iostream>

class Widget {
	int data;
public:
	Widget(int n): data(n) {}
	int get() const {
		return data;
	}
	void set(int val) {
		data = val;
	}
};

class Gadget {
	Widget wid;
public:
	Gadget(int n) : wid(n) {
		//wid.set(n);
	}
	int get() const {
		return wid.get();
	}
};

int main() {
	Gadget gad{ 34 };
	std::cout << gad.get() << '\n';
}
