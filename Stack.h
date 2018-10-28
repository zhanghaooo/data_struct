#pragma once
#include<exception>
#include"Array.h"

template <typename T>
class Stack {
private:
	Array<T> array;
public:
	void push(const T &e) {
		this->array.pushBack(e);
	}

	T pop() {
		T tem = this->array[this->array.getSize() - 1];
		this->array.erase(this->array.getSize() - 1);
		return tem;
	}

	T top() {
		return this->array[this->array.getSize() - 1];
	}

	bool empty() {
		return this->array.getSize() == 0;
	}

	unsigned int getSize() {
		return this->array.getSize();
	}

	unsigned int getCapacity() {
		return this->array.getCapacity();
	}
};
