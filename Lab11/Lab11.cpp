
#include <iostream>
using namespace std;
enum Color { Red, Black };
struct Node {
	int value;
	Node* left;
	Node* right;
	Node* parent;
	Color color;
	int height;
	Node(int _value) : value(_value), left(nullptr), right(nullptr), parent(nullptr), color(Red), height(1) {}
	Node() : value(0), left(nullptr), right(nullptr), parent(nullptr), color(Black), height(0) {}
};
struct RedBlackTree {
	Node* head = nullptr;
	Node* rotateRight(Node*& root) {
		Node* newRoot = root->left;
		root->left = newRoot->right;
		if (newRoot->right != nullptr) {
			newRoot->right->parent = root;
		}
		newRoot->parent = root->parent;
		if (root->parent == nullptr) {
			head = newRoot;
		}
		else if (root == root->parent->left) {
			root->parent->left = newRoot;
		}
		else {
			root->parent->right = newRoot;
		}
		newRoot->right = root;
		root->parent = newRoot;
		if (root == head) {
			head = newRoot;
		}
		return newRoot;
	}
	Node* rotateLeft(Node*& root) {
		Node* newRoot = root->right;
		root->right = newRoot->left;
		if (newRoot->left != nullptr) {
			newRoot->left->parent = root;
		}
		newRoot->parent = root->parent;
		if (root->parent == nullptr) {
			head = newRoot;
		}
		else if (root == root->parent->left) {
			root->parent->left = newRoot;
		}
		else {
			root->parent->right = newRoot;
		}
		newRoot->left = root;
		root->parent = newRoot;
		if (root == head) {
			head = newRoot;
		}
		return newRoot;
	}
	void insert(Node* newNode, Node*& current) {

		if (head == nullptr) {
			head = newNode;
			head->color = Black;
			head->left = new Node();
			head->left->parent = head;
			head->right = new Node();
			head->right->parent = head;
			return;
		}
		if (newNode->value > current->value) {
			if (current->value == 0) {
				Node* parrent = current->parent;
				current = newNode;
				current->parent = parrent;
				current->color = Red;
				current->right = new Node();
				current->right->parent = current;
				current->left = new Node();
				current->left->parent = current;
				return;
			}
			insert(newNode, current->right);
		}
		else if (newNode->value < current->value) {
			if (current->value == 0) {
				Node* parrent = current->parent;
				current = newNode;
				current->parent = parrent;
				current->color = Red;
				current->right = new Node();
				current->right->parent = current;
				current->left = new Node();
				current->left->parent = current;
				return;
			}
			insert(newNode, current->left);
		}
		while (newNode->parent != nullptr && newNode->parent->color == Red) {
			Node* grandparent = newNode->parent->parent;
			if (newNode->parent == grandparent->left) {
				Node* uncle = grandparent->right;

				if (uncle != nullptr && uncle->color == Red) {
					newNode->parent->color = Black;
					uncle->color = Black;
					grandparent->color = Red;
					newNode = grandparent;
				}
				else {
					if (newNode == newNode->parent->right) {
						newNode = newNode->parent;
						rotateLeft(newNode);
					}

					newNode->parent->color = Black;
					grandparent->color = Red;
					rotateRight(grandparent);
				}
			}
			else {
				Node* uncle = grandparent->left;

				if (uncle != nullptr && uncle->color == Red) {
					newNode->parent->color = Black;
					uncle->color = Black;
					grandparent->color = Red;
					newNode = grandparent;
				}
				else {
					if (newNode == newNode->parent->left) {
						newNode = newNode->parent;
						rotateRight(newNode);
					}

					newNode->parent->color = Black;
					grandparent->color = Red;
					rotateLeft(grandparent);
				}
			}
		}
		head->color = Black;
	}
	void print(Node* node) {
		if (node == NULL) { return; }
		if (node->value != 0) {
			cout << node->value << " ";
			if (node->color == Black) {
				cout << "Black" << endl;
			}
			else if (node->color == Red) {
				cout << "Red" << endl;
			}
		}

		print(node->left);
		print(node->right);
	}
	Node* minValue(Node* current) {
		Node* prev;
		while (current->left != nullptr) {
			prev = current;
			current = current->left;
			prev->left = nullptr;
		}
		return current;
	}
	Node* maxValue(Node* current) {
		Node* prev;
		while (current->right != nullptr) {
			prev = current;
			current = current->right;
			prev->right = nullptr;
		}
		return current;
	}
	void deleteNode(int _value) {
		Node* current = head;
		Node* prev = nullptr;
		while (current->value != _value) {
			prev = current;
			if (_value > current->value) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		if (current->left == nullptr && current->right == nullptr) {
			if (current == head) {
				head = nullptr;
				return;
			}
			if (prev->left == current) {
				prev->left = nullptr;
			}
			else if (prev->right == current) {
				prev->right = nullptr;
			}
		}
		else if (current->left != nullptr && current->right == nullptr) {
			if (current == head) {
				head = head->left;
				return;
			}
			if (prev->left == current) {
				prev->left = current->left;
			}
			else if (prev->right == current) {
				prev->right = current->left;
			}
		}
		else if (current->right != nullptr && current->left == nullptr) {
			if (current == head) {
				head = head->right;
				return;
			}
			if (prev->left == current) {
				prev->left = current->right;
			}
			else if (prev->right == current) {
				prev->right = current->right;
			}
		}
		else {
			if (current == head) {
				Node* temp = head;
				head = head->right;
				head->left = temp->left;
				return;
			}
			if (prev->left == current) {
				prev->left = maxValue(current->left);
				if (prev->left == current->left) {
					current->left = nullptr;
				}
				prev->left->right = current->right;
				prev->left->left = current->left;
			}
			else if (prev->right == current) {
				prev->right = maxValue(current->left);
				if (prev->right == current->left) {
					current->left = nullptr;
				}
				prev->right->right = current->right;
				prev->right->left = current->left;

			}
		}
	}
};
int main()
{
	RedBlackTree tree;
	/*tree.insert(new Node(5), tree.head);
	tree.insert(new Node(1), tree.head);
	tree.insert(new Node(20), tree.head);
	tree.insert(new Node(11), tree.head);
	tree.insert(new Node(25), tree.head);
	tree.insert(new Node(7), tree.head);
	tree.insert(new Node(15), tree.head);
	tree.insert(new Node(55), tree.head);
	tree.insert(new Node(17), tree.head);*/
	tree.insert(new Node(24), tree.head);
	tree.insert(new Node(5), tree.head);
	tree.insert(new Node(1), tree.head);
	tree.print(tree.head);
}
