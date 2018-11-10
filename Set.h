#pragma once
#include"BST.h"

template<typename T>
class Set {
private:
	BST<T> bst_;
public:
	bool empty() {
		return bst_.empty();
	}

	unsigned int size() {
		return bst_.size();
	}

	void insert(const T e) {
		bst_.insert(e);
	}

	void erase(const T &e) {
		bst_.erase(e);
	}

	bool find(const T &e) {
		return bst_.find(e);
	}
};