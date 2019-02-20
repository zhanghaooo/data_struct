#pragma once
#include<algorithm>
#include"Stack.h"

template<typename T>
class AVLTree {
	using size_t = unsigned int;
private:
	struct Node
	{
		T value;
		size_t height = 1;
		Node *left;
		Node *right;

		Node(T e) :value(e), left(nullptr), right(nullptr) {}
	};

	Node *root_;
	size_t size_;

	size_t get_height(Node *root)
	{
		if (!root)
			return 0;
		return root->height;
	}

	int get_balance(Node *root)
	{
		if (!root)
			return 0;
		return int(get_height(root->left)) - int(get_height(root->right));
	}

	//   y                           x
	//  / \                        /   \
	// T1  x     turn_left(y)     y     z  
	//    / \   -------------->  / \   / \
	//   T2  z                  T1 T2 T3 T4
	//      / \                 
	//     T3 T4                
	Node* left_rotate(Node* y)
	{
		Node* x = y->right;
		y->right = x->left;
		x->left = y;
		y->height = max(get_height(y->left), get_height(y->right)) + 1;
		x->height = max(get_height(x->left), get_height(x->right)) + 1;
		return x;
	}

	//       z                          x
	//      / \                       /   \
	//     x  T4   turn_right(z)     y     z
	//    / \     -------------->   / \   / \
	//   y  T3                     T1 T2 T3 T4
	//  / \
	// T1 T2
	Node* right_rotate(Node* z)
	{
		Node* x = z->left;
		z->left = x->right;
		x->right = z;
		z->height = max(get_height(z->left), get_height(z->right)) + 1;
		x->height = max(get_height(x->left), get_height(x->right)) + 1;
		return x;
	}

	Node* insert(Node *root, T e) 
	{
		if (!root) {
			++size_;
			return new Node(e);
		}
		if (root->value == e)
			return root;
		if (root->value > e)
			root->left = insert(root->left, e);
		else
			root->right = insert(root->right, e);
		root->height = max(get_height(root->left), get_height(root->right)) + 1;

		//make the bst balance
		if (get_balance(root) > 1) {
			if (get_balance(root->left) < 0)
				root->left = left_rotate(root->left);
			return right_rotate(root);
		} 
		if (get_balance(root) < -1) {
			if (get_balance(root->right) > 0)
				root->right = right_rotate(root->right);
			return left_rotate(root);
		}
		return root;
	}

	Node* erase(Node* root, T e)
	{
		if (!root)
			return nullptr;
		if (e == root->value) {
			if (root->left && root_->right) {
				Node* p = root->right;
				while (p->left)
					p = p->left;
				root->value = p->value;
				root->right = erase(root->right, p->value);
			}
			else {
				root = (root->left) ? root->left : root->right;
				--size_;
			}
			return root;
		}
		if (e < root->value)
			root->left = erase(root->left, e);
		else
			root->right = erase(root->right, e);
		root->height = max(get_height(root->left), get_height(root->right)) + 1;

		//make the bst balance
		if (get_balance(root) > 1) {
			if (get_balance(root->left) < 0)
				root->left = left_rotate(root->left);
			return right_rotate(root);
		}
		if (get_balance(root) < -1) {
			if (get_balance(root->right) > 0)
				root->right = right_rotate(root->right);
			return left_rotate(root);
		}
		return root;
	}

	bool is_balanced(Node* root)
	{
		if (!root)
			return true;
		if (abs(get_balance(root)) > 1)
			return false;
		return abs(get_balance(root)) <= 1 
			&& is_balanced(root->left) 
			&& is_balanced(root->right);
	}

public:
	AVLTree() :root_(nullptr), size_(0) {}

	size_t size()
	{
		return size_;
	}

	bool empty()
	{
		return size_ == 0;
	}

	void insert(T e)
	{
		root_ = insert(root_, e);
	}

	void erase(const T &e)
	{
		root_ = erase(root_, e);
	}

	bool find(const T &e)
	{
		Node *p = root_;
		while (p) {
			if (p->value == e)
				return true;
			p = (e < p->value) ? p->left : p->right;
		}
		return false;
	}

	bool is_balanced()
	{
		return is_balanced(root_);
	}

	friend std::ostream& operator << (std::ostream &os, const AVLTree<T> &bst)
	{
		Stack<Node*> s;
		Node* p = bst.root_;
		while (p || !s.empty()) {
			while (p) {
				s.push(p);
				p = p->left;
			}
			p = s.pop();
			os << p->value << " ";
			p = p->right;
		}
		return os;
	}
};