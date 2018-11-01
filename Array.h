#pragma once
#include<exception>

template<typename T>
class Array {
private:
	T* data;
	unsigned int size;
	unsigned int capacity;
public:
	Array() : size(0), capacity(10), data(new T[10]) {}
	Array(unsigned int n) : size(n), capacity(2*n), data(new T[2*n]) {}

	~Array() {
		delete[] this->data;
		this->size = 0;
		this->capacity = 0;
	}

	unsigned int getSize() {
		return this->size;
	}

	unsigned int getCapacity() {
		return this->capacity;
	}

	bool isEmpty() {
		return this->size == 0;
	}

	void resize(const unsigned int &n) {
		T *tem = new T[n];
		for (unsigned int i = 0; i < this->size; ++i)
			tem[i] = this->data[i];
		delete[] this->data;
		this->data = tem;
		this->capacity = n;
	}

	void insert(const unsigned int &index, const T e) {
		if (index > this->size)
			throw std::out_of_range("array subscript out of range");
		if (this->size == this->capacity)
			this->resize(this->capacity * 2);
		for (unsigned int i = this->size; i > index; --i)
			this->data[i] = this->data[i - 1];
		this->data[index] = e;
		++this->size;
	}

	void pushBack(const T e) {
		this->insert(this->size, e);
	}

	void erase(const unsigned int &index) {
		if (index >= this->size)
			throw std::out_of_range("array subscript out of range");
		for (unsigned int i = index; i < this->size - 1; ++i)
			this->data[i] = this->data[i + 1];
		--this->size;
		if (this->size == this->capacity / 4 && this->capacity > 1)
			this->resize(this->capacity / 2);
	}

	void popBack() {
		this->erase(this->size - 1);
	}

	T& operator[](const unsigned int &index) {
		if (index >= this->size)
			throw std::out_of_range("array subscript out of range");
		return this->data[index];
	}

	unsigned int find(const T &e) {
		for (unsigned int i = 0; i < this->size; ++i) {
			if (this->data[i] == e)
				return i;
		}
		return this->size;
	}

	unsigned int count(const T &e) {
		unsigned int n = 0;
		for (unsigned int i = 0; i < this->size; ++i) {
			if (this->data[i] == e)
				++n;
		}
		return n;
	}

	void reverse() {
		for (unsigned int i = 0; i < this->size/2; ++i) {
			T tem = this->data[i];
			this->data[i] = this->data[this->size - 1 - i];
			this->data[this->size - 1 - i] = tem;
		}
	}
};