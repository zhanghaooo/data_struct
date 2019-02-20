#pragma once

#include <iostream>
#include "Vector.h"
#include "Queue.h"
using namespace std;

template<typename T>
class BinaryTree {
private:
	struct Node {
		T value_;
		Node *left_;
		Node *right_;

		Node(int value) : value_(value), left_(nullptr), right_(nullptr) {}
	};

	Node* root_;

public:
	BinaryTree(Vector<T> &v) {
		if (v.empty())
			return;
		root_ = new Node(v[0]);
		if (v.size() == 1)
			return;
		Queue<Node*> leaves;
		leaves.push(root_);
		int k = 0;
		while (!leaves.empty()) {
			Node* p = leaves.pop();
			if (p) {
				if (k < v.size() - 1) {
					p->left_ = v[++k]? new Node(v[k]) : NULL;
					leaves.push(p->left_);
				}
				if (k < v.size() - 1) {
					p->right_ = v[++k] ? new Node(v[k]) : NULL;
					leaves.push(p->right_);
				}
			}
		}
	}

	Vector<T> toVector() {
		Vector<T> v;
		Queue<Node*> leaves;
		leaves.push(root_);
		while (!leaves.empty()) {
			Node* p = leaves.pop();
			if (p) {
				v.push_back(p->value_);
				if (p->left_)
					leaves.push(p->left_);
				else
					leaves.push(NULL);
				if (p->right_)
					leaves.push(p->right_);
				else
					leaves.push(NULL);
			}
			else {
				v.push_back(NULL);
			}
		}
		while (!v.back()) {
			v.pop_back();
		}
		return v;
	}
};
