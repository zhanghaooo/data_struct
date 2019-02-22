#pragma once
#include"Stack.h"

template<typename T>
class RBTree {
	using size_t = unsigned int;
private:
	static const bool RED = true, BLACK = false;
	struct Node
	{
		T value_;
		bool color_ = RED;
		Node *left_ = nullptr;
		Node *right_ = nullptr;
		Node *parent_ = nullptr;
		Node(T e) : value_(e) {}
	};

	Node *root_ = nullptr;
	size_t size_ = 0;

	bool color(Node* x)
	{
		return (x == nullptr) ? BLACK : x->color_;
	}

	//   x       left_rotate(x)       y
	//  / \    ----------------->    / \
	// T1  y   <-----------------   x  T3
	//    / \    right_rotate(y)   / \ 
	//   T2 T3                    T1 T2
	void left_rotate(Node *x)
	{
		Node* y = x->right_;
		x->right_ = y->left_;
		if (y->left_)
			y->left_->parent_ = x;
		y->parent_ = x->parent_;
		if (x->parent_ == nullptr) {
			root_ = y;
		}
		else {
			if (x == x->parent_->left_)
				x->parent_->left_ = y;
			else
				x->parent_->right_ = y;
		}
		y->left_ = x;
		x->parent_ = y;
	}

	void right_rotate(Node* y)
	{
		Node* x = y->left_;
		y->left_ = x->right_;
		if (x->right_)
			x->right_->parent_ = y;
		x->parent_ = y->parent_;
		if (y->parent_ == nullptr) {
			root_ = x;
		}
		else {
			if (y == y->parent_->left_)
				y->parent_->left_ = x;
			else
				y->parent_->right_ = x;
		}
		x->right_ = y;
		y->parent_ = x;
	}

public:

	size_t size()
	{
		return size_;
	}

	bool empty()
	{
		return size_ == 0;
	}

	bool find(const T &e)
	{
		Node *x = root_;
		while (x) {
			if (x->value_ == e)
				return true;
			x = (e < x->value_) ? x->left_ : x->right_;
		}
		return false;
	}

	void insert(T e)
	{
		Node *y = nullptr, *x = root_;
		while (x != nullptr) {
			y = x;
			if (e < x->value_)
				x = x->left_;
			else if (e > x->value_)
				x = x->right_;
			else
				return;
		}
		Node* z = new Node(e);
		z->parent_ = y;
		if (y == nullptr)
			root_ = z;
		else if (z->value_ < y->value_)
			y->left_ = z;
		else
			y->right_ = z;
		++size_;
		// RB_INSERT_FIXUP
		while (color(z->parent_) == RED) {
			if (z->parent_ == z->parent_->parent_->left_) {
				y = z->parent_->parent_->right_;
				if (color(y) == RED) {
					z->parent_->color_ = BLACK;
					y->color_ = BLACK;
					z->parent_->parent_->color_ = RED;
					z = z->parent_->parent_;
				}
				else {
					if (z == z->parent_->right_) {
						z = z->parent_;
						left_rotate(z);
					}
					z->parent_->color_ = BLACK;
					z->parent_->parent_->color_ = RED;
					right_rotate(z->parent_->parent_);
				}
			}
			else {
				y = z->parent_->parent_->left_;
				if (color(y) == RED) {
					z->parent_->color_ = BLACK;
					y->color_ = BLACK;
					z->parent_->parent_->color_ = RED;
					z = z->parent_->parent_;
				}
				else {
					if (z = z->parent_->left_) {
						z = z->parent_;
						right_rotate(z);
					}
					z->parent_->color_ = BLACK;
					z->parent_->parent_->color_ = RED;
					left_rotate(z->parent_->parent_);
				}
			}
		}
		root_->color = BLACK;
	}

	void erase(const T &e)
	{
		
	}

	friend std::ostream& operator << (std::ostream &os, const RBTree<T> &bst)
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