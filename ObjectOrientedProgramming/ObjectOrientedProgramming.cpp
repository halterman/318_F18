// ObjectOrientedProgramming.cpp
// Created 10/5/2018 10:09:42 AM

#include <iostream>
#include <vector>
#include <ctime>

int sn_source = 1;

class Fruit {
protected:
	int serial_number;
public:
	Fruit() : serial_number(sn_source++) {}
	virtual void id() const = 0;
};

class Apple : public Fruit {
public:
	Apple() {}
};

class GoldenDelicious : public Apple {
public:
	GoldenDelicious() {}
	void id() const override {
		std::cout << "golden delicious apple #" << serial_number << '\n';
	}
};

class Gala : public Apple {
public:
	Gala() {}
	void id() const override {
		std::cout << "gala apple #" << serial_number << '\n';
	}
};

class Banana : public Fruit  {
	int more_data;
public:
	Banana() {}
	void id() const override {
		std::cout << "banana #" << serial_number << '\n';
	}
};

int main() {
	srand(time(0));
	std::vector<Gala> apple_cart {Gala(), Gala(), Gala(), Gala()};
	std::vector<Banana> banana_boat {Banana(), Banana()};
	std::vector<Fruit *> fruit_basket { new Gala, new Banana, new GoldenDelicious};
    
	for (auto& item : apple_cart)
		item.id();

	for (auto& item : banana_boat)
		item.id();

	std::cout << "----------------------\n";

	if (rand() % 2 == 0) {
		fruit_basket.push_back(new Gala);
	}
	else {
		fruit_basket.push_back(new Banana);
	}

	for (auto& item : fruit_basket)
		item->id();

}
