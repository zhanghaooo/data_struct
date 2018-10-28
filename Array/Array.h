#pragma once

template<typename T>
class Array {
private:
	T* data;
	unsigned int size;
	unsigned int capacity;
public:
	Array() : size(0), capacity(10), data(new T[capacity]()) {}
	Array(unsigned int n) : size(n), capacity(2 * size), data(new T[capacity]()) {}

	unsigned int size() {
		return this->size;
	}

	unsigned int getCapacity() {
		return this->capacity;
	}

	bool isEmpty() {
		return this->size == 0;
	}

	void insert(unsigned int index, T e) {
		if (index > this->size)
			throw out_of_range("array subscript out of range");
		if (this->size == this->capacity) {
			T *tem = new T[2 * this->capacity]();
			for (unsigned int i = 0; i < this->size; ++i)
				tem[i] = this->data[i];
			delete[] this->data;
			this->data = tem;
			this->capacity *= 2;
		}
		for (unsigned int i = this->size; i > index; --i)
			this->data[i] = this->data[i - 1];
		this->data[index] = e;
		++this->size;
	}

	void pushBack(T e) {
		this->insert(this->size, e);
	}

	void erase(unsigned int index) {
		if (index >= this->size)
			throw out_of_range("array subscript out of range");
		for (unsigned int i = index; i < this->size - 1; ++i)
			this->data[i] = this->data[i + 1];
		--this->size;
		if (this->size == this->capacity / 4 && this->capacity > 1) {
			T *tem = new T[this->capacity / 2]();
			for (unsigned int i = 0; i < this->size; ++i)
				tem[i] = this->data[i];
			delete[] this->data;
			this->data = tem;
			this->capacity /= 2;
		}
	}

	void popBack() {
		this->erase(this->size - 1);
	}

	T& operator[](unsigned int index) {
		if (index >= this->size)
			throw out_of_range("array subscript out of range");
		return this->data[index];
	}

	unsigned int find(T e) {
		for (unsigned int i = 0; i < this->size; ++i) {
			if (this->data[i] == e)
				return i;
		}
		return this->size;
	}

	unsigned int count(T e) {
		unsigned int n = 0;
		for (unsigned int i = 0; i < this->size; ++i) {
			if (this->data[i] == e)
				++n;
		}
		return n;
	}

};