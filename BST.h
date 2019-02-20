#pragma once
#include"Stack.h"

template<typename T>
class BST {
	using size_t = unsigned int;
private:
	struct Node 
	{
		T value;
		Node *left;
		Node *right;

		Node(T e) :value(e), left(nullptr), right(nullptr) {}
	};

	Node *root_;
	size_t size_;

	T pop_max(Node *&root) 
	{
		if (!root)
			return NULL;
		--size_;
		T maximum;
		if (!root->right) {
			maximum = root->value;
			root = root->left;
			return maximum;
		}
		Node *p = root;
		while (p->right->right)
			p = p->right;
		maximum = p->right->value;
		p->right = p->right->left;
		return maximum;
	}

	T pop_min(Node *&root) 
	{
		if (!root)
			return NULL;
		--size_;
		T minimum;
		if (!root->left) {
			minimum = root->value;
			root = root->right;
			return minimum;
		}
		Node *p = root;
		while (p->left->left)
			p = p->left;
		minimum = p->left->value;
		p->left = p->left->right;
		return minimum;
	}

public:
	BST() :root_(nullptr), size_(0) {}
	
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
		Node **p = &root_; 
		while (*p) {
			if ((*p)->value == e)
				return;
			p = (e < (*p)->value) ? &(*p)->left : &(*p)->right;
		}
		*p = new Node(e);
		++size_;
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

	T pop_max() 
	{
		return pop_max(root_);
	}

	T pop_min() 
	{
		return pop_min(root_);
	}

	void erase(const T &e) 
	{
		Node *pre = NULL, *p = root_;
		while (p && p->value != e) {
			pre = p;
			p = (p->value < e) ? p->right : p->left;
		}
		if (!p)
			return;
		if (p == root_) {
			if (root_->left && root_->right)
				root_->value = pop_min(root_->right);
			else {
				root_ = (root_->left) ? root_->left : root_->right;
				--size_;
			}
			return;
		}

		if (p->left && p->right) 
			p->value = pop_min(p->right);
		else { 
			--size_;
			if (p->value < pre->value)
				pre->left = (p->left) ? p->left : p->right;
			else
				pre->right = (p->left) ? p->left : p->right;
		}
	}

	friend std::ostream& operator << (std::ostream &os, const BST<T> &bst)
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