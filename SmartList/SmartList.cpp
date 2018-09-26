// SmartList.cpp
// Created 9/14/2018 10:11:11 AM

#include <iostream>
#include <memory>

template <typename T>
class DumbList {
	struct Node {
		T data;
		Node *next;
		Node(const T& item, Node *nxt) : data(item), next(nxt) {
			std::cout << "Creating a node with value " << data << '\n';
		}
		~Node() {
			std::cout << "Destroying a node with value " << data << '\n';
		}
	};
	Node *head;  // Points to the first element in the list

	void dump2(Node *p) const {
		if (p) {
			std::cout << p->data << ' ';
			dump2(p->next);
		}
	}

public:
	DumbList() : head(nullptr) {
		std::cout << "Creating a dumb list\n";
	}
	~DumbList() {
		std::cout << "Destroying a dumb list\n";
		// Clean up the memory held by the list's nodes
		while (head) {
			auto temp = head;
			head = head->next;
			delete temp;
		}
	}

	void insert(const T& item) {
		head = new Node(item, head);
	}

	void dump() const {
		for (auto cursor = head; cursor; cursor = cursor->next) 
			std::cout << cursor->data << ' ';
		std::cout << '\n';
	}
	void dump2() const {
		dump2(head);
		std::cout << '\n';
	}

};

template <typename T>
class SmartList {
	struct Node {
		T data;
		std::shared_ptr<Node> next;
		Node(const T& item, std::shared_ptr<Node> nxt) : data(item), next(nxt) {
			std::cout << "Creating a node with value " << data << '\n';
		}
		~Node() {
			std::cout << "Destroying a node with value " << data << '\n';
		}
	};
	std::shared_ptr<Node> head;  // Points to the first element in the list

public:
	SmartList() : head(nullptr) {
		std::cout << "Creating a smart list\n";
	}
	~SmartList() {
		std::cout << "Destroying a smart list\n";
		// Clean up the memory held by the list's nodes
		//while (head) {
		//	auto temp = head;
		//	head = head->next;
		//	delete temp;
		//}
	}

	void insert(const T& item) {
		head = std::make_shared<Node>(item, head);
	}

	void dump() const {
		for (auto cursor = head; cursor; cursor = cursor->next)
			std::cout << cursor->data << ' ';
		std::cout << '\n';
	}

};



void test_dumb_list() {
	DumbList<int> lst;
	for (int i = 1; i < 6; i++)
		lst.insert(10 * i);
	lst.dump();
	lst.dump2();
} 

void test_smart_list() {
	SmartList<int> lst;
	for (int i = 1; i < 6; i++)
		lst.insert(100 * i);
	lst.dump();
}


int main() {
	std::cout << "Starting main function\n";
	test_dumb_list();
	std::cout << "--------------------------\n";
	test_smart_list();
	std::cout << "Finishing main function\n";
    
}
