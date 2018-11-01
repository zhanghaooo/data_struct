#pragma once
#include<exception>

template <typename T>
class List {
private:
	class Node {
	public:
		T value;
		Node* next;
		Node() : value(NULL), next(NULL) {}
		Node(T e, Node* n) :value(e), next(n) {}
	};
	Node *head;
	unsigned int size;

public:
	List() : head(new Node()), size(0) {}

	unsigned int getSize() {
		return this->size;
	}

	bool empty() {
		return this->size == 0;
	}

	void add(const unsigned int &index, const T e) {
		if (index > this->size)
			throw std::out_of_range("list subscript out of range");

		Node* pre = this->head;
		for (unsigned int i = 0; i < index; ++i)
			pre = pre->next;
		pre->next = new Node(e, pre->next);
		++this->size;
	}

	void addFirst(const T e) {
		this->add(0, e);
	}

	void addLast(const T e) {
		this->add(this->size, e);
	}

	void erase(const unsigned int *index) {
		if (index >= this->size)
			throw std::out_of_range("list subscript out of range");

		Node* pre = this->head;
		for (unsigned int i = 0; i < index; ++i)
			pre = pre->next;
		pre->next = pre->next->next;
		--this->size;
	}

	T& operator[](const unsigned int &index) {
		if (index >= this->size)
			throw std::out_of_range("list subscript out of range");
		Node* cur = this->head->next;
		for (unsigned int i = 0; i < index; ++i)
			cur = cur->next;
		return cur->value;
	}

	bool find(const T &e) {
		Node* cur = this->head;
		while (cur->next && cur->next->value != e) 
			cur = cur->next;
		return cur;
	}
};