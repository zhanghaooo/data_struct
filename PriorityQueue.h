#pragma once
#include"Heap.h"

template<typename T>
class PriorityQueue{
private:
	Heap<T> heap_;
public:
	PriorityQueue(bool(*cmp)(const T &e1, const T &e2)) : heap_(Heap<T>(cmp)) {};

	void push(T e) 
	{
		heap_.push(e);
	}

	T pop()
	{
		return heap_.pop();
	}

	T top()
	{
		return heap_.top();
	}

	bool empty()
	{
		return heap_.empty();
	}

	bool size()
	{
		return heap_.size();
	}
};

