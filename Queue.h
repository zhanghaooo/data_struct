#pragma once
#include<exception>

template<typename T>
class Queue {
private:
	T *data;
	unsigned int front, tail;
	unsigned int size;
	unsigned int capacity;
public:
	Queue() : data(new T[10]), front(0), tail(0), size(0), capacity(10) {}
	Queue(unsigned int n) : data(new T[n]), front(0), tail(0), size(0), capacity(n) {}
	~Queue() {
		delete[] this->data;
	}

	bool empty() {
		return this->size == 0;
	}
	
	unsigned int getSize() {
		return this->size;
	}

	unsigned int getCapacity() {
		return this->capacity;
	}

	void resize(const unsigned int &n) {
		T *tem = new T[n];
		for (unsigned int i = 0; i < this->size; ++i)
			tem[i] = this->data[(this->front + i) % this->capacity];
		delete[] this->data;
		this->data = tem;
		this->capacity = n;
		this->front = 0;
		this->tail = this->size;
	}

	void pushBack(const T &e) {
		if (this->size == this->capacity)
			this->resize(this->capacity * 2);
		this->data[this->tail] = e;
		this->tail = (this->tail + 1) % this->capacity;
		++this->size;
	}

	T& popFront() {
		if (this->empty())
			throw std::out_of_range("the queue is empty");

		T e = this->data[this->front];
		this->front = (this->front + 1) % this->capacity;
		--this->size;
		if (this->size == this->capacity / 4 && this->capacity > 1)
			this->resize(this->capacity / 2);
		return e;
	}

	T& operator[](const unsigned int &index) {
		if (index >= this->size)
			throw std::out_of_range("queue subscript out of range");
		return this->data[(this->front + index) % this->capacity];
	}

	T& getFront() {
		return this->data[this->front];
	}


	
};
