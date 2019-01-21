#pragma once
#include<exception>
#include"Vector.h"

template <typename T>
class Stack {
private:
	Vector<T> data_;
public:
	bool empty() {
		return data_.size() == 0;
	}

	void push(const T e) {
		data_.push_back(e);
	}

	T& pop() {
		if (empty())
			throw std::out_of_range("the stack is empty");
		T tem = data_[data_.size() - 1];
		data_.erase(data_.size() - 1);
		return tem;
	}

	T& top() {  
		return data_[data_.size() - 1];
	}

	unsigned int size() {
		return data_.size();
	}

	unsigned int capacity() {
		return data_.capacity();
	}
};
