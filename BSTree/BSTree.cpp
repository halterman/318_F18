// BSTree.cpp
// Created 9/28/2018 10:24:18 AM

#include <iostream>

template <typename T>
class BSTree {
	struct Node {
		T data;
		Node *left;
		Node *right;
		Node(int data) : data(data), left(nullptr), right(nullptr) {}
	};

	Node *root;

	Node *insert(Node *t, const T& item) {
		if (!t) {
			t = new Node(item);
		}
		else if (item < t->data)
			t->left = insert(t->left, item);
		else if (item > t->data) 
			t->right = insert(t->right, item);
		// else do not insert a duplicate
		return t;
	}
	static void spaces(int depth) {
		while (depth) {
			depth--;
			std::cout << ' ';
		}
	}
	void display(Node *t, int depth, char link) const {
		if (t) {
			display(t->right, depth + 5, '/');
			spaces(depth);
			std::cout << link << '[' << t->data << ']' << '\n';
			display(t->left, depth + 5, '\\');
		}
	}
public:
	BSTree() : root(nullptr) {}
	~BSTree() {
		// TODO:  Need to destroy all the nodes in this tree
	}
	void insert(const T& item) {
		root = insert(root, item);
	}
	void display() const {
		display(root, 0, '-');
	}
};

int main() {
	BSTree<int> tree;

	tree.insert(16);
	tree.insert(8);
	tree.insert(3);
	tree.insert(22);
	tree.insert(19);
	tree.insert(20);
	tree.insert(34);
	tree.insert(7);

	tree.display();
}
