#pragma once
#include<exception>
#include"Array.h"

template <typename T>
class Stack {
private:
	Array<T> *data;
public:
	Stack() : data(new Array<T>()) {}
	Stack(unsigned int n) : data(new Array<T>(n)) {}

	bool empty() {
		return this->data->getSize() == 0;
	}

	void push(const T e) {
		this->data->pushBack(e);
	}

	T& pop() {
		if (this->empty())
			throw std::out_of_range("the stack is empty");
		T tem = (*this->data)[this->data->getSize() - 1];
		this->data->erase(this->data->getSize() - 1);
		return tem;
	}

	T& top() {
		return (*this->data)[this->data->getSize() - 1];
	}

	unsigned int getSize() {
		return this->data->getSize();
	}

	unsigned int getCapacity() {
		return this->data->getCapacity();
	}
};
