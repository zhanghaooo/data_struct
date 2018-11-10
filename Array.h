#pragma once
#include<exception>

template<typename T>
class Array {
private:
	T* data_;
	unsigned int size_;
	unsigned int capacity_;
public:
	Array() : size_(0), capacity_(10), data_(new T[10]) {}
	Array(unsigned int n) : size_(n), capacity_(2 * n), data_(new T[2 * n]) {}

	~Array() {
		delete[] data_;
		size_ = 0;
		capacity_ = 0;
	}

	unsigned int size() {
		return size_;
	}

	unsigned int capacity() {
		return capacity_;
	}

	bool empty() {
		return size_ == 0;
	}

	void clear() {
		size_ = 0;
	}

	void resize(const unsigned int &n) {
		T *tem = new T[n];
		for (unsigned int i = 0; i < size_; ++i)
			tem[i] = data_[i];
		delete[] data_;
		data_ = tem;
		capacity_ = n;
	}

	void insert(const unsigned int &index, const T e) {
		if (index > size_)
			throw std::out_of_range("array subscript out of range");
		if (size_ == capacity_)
			resize(capacity_ * 2);
		for (unsigned int i = size_; i > index; --i)
			data_[i] = data_[i - 1];
		data_[index] = e;
		++size_;
	}

	void push_back(const T e) {
		insert(size_, e);
	}

	void erase(const unsigned int &index) {
		if (index >= size_)
			throw std::out_of_range("array subscript out of range");
		for (unsigned int i = index; i < size_ - 1; ++i)
			data_[i] = data_[i + 1];
		--size_;
		if (size_ == capacity_ / 4 && capacity_ > 1)
			resize(capacity_ / 2);
	}

	void pop_back() {
		erase(size_ - 1);
	}

	T& operator[](const unsigned int &index) {
		if (index >= size_)
			throw std::out_of_range("array subscript out of range");
		return data_[index];
	}

	unsigned int find(const T &e) {
		for (unsigned int i = 0; i < size_; ++i) {
			if (data_[i] == e)
				return i;
		}
		return size_;
	}

	unsigned int count(const T &e) {
		unsigned int n = 0;
		for (unsigned int i = 0; i < size_; ++i) {
			if (data_[i] == e)
				++n;
		}
		return n;
	}

	void reverse() {
		for (unsigned int i = 0; i < size_ / 2; ++i) {
			T tem = data_[i];
			data_[i] = data_[size_ - 1 - i];
			data_[size_ - 1 - i] = tem;
		}
	}
};