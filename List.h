#pragma once
#include<exception>

template <typename T>
class List {
private:
	struct Node {
		T value;
		Node* next;
		Node() : value(NULL), next(NULL) {}
		Node(T e, Node* n) :value(e), next(n) {}
	};

	Node *head_;
	unsigned int size_;

public:
	List() : head_(new Node()), size_(0) {}

	unsigned int size() {
		return size_;
	}

	bool empty() {
		return size_ == 0;
	}

	void insert(const unsigned int &index, const T e) {
		if (index > size_)
			throw std::out_of_range("list subscript out of range");

		Node* pre = head_;
		for (unsigned int i = 0; i < index; ++i)
			pre = pre->next;
		pre->next = new Node(e, pre->next);
		++size_;
	}

	void push_front(const T e) {
		insert(0, e);
	}

	void erase(const unsigned int &index) {
		if (index >= size_)
			throw std::out_of_range("list subscript out of range");

		Node* pre = head_;
		for (unsigned int i = 0; i < index; ++i)
			pre = pre->next;
		pre->next = pre->next->next;
		--size_;
	}

	T& operator[](const unsigned int &index) {
		if (index >= size_)
			throw std::out_of_range("list subscript out of range");

		Node* p = head_->next;
		for (unsigned int i = 0; i < index; ++i)
			p = p->next;
		return p->value;
	}

	bool find(const T &e) {
		Node* p = head_;
		while (p->next && p->next->value != e) 
			p = p->next;
		return p;
	}
};