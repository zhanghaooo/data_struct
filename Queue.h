#pragma once
#include<exception>

template<typename T>
class Queue {
private:
	T *data_;
	unsigned int front_, tail_;
	unsigned int size_;
	unsigned int capacity_;
public:
	Queue() : data_(new T[10]), front_(0), tail_(0), size_(0), capacity_(10) {}
	Queue(unsigned int n) : data_(new T[n]), front_(0), tail_(0), size_(0), capacity_(n) {}
	~Queue() {
		delete[] data_;
	}

	bool empty() {
		return size_ == 0;
	}
	
	unsigned int size() {
		return size_;
	}

	unsigned int capacity() {
		return capacity_;
	}

	void resize(const unsigned int &n) {
		T *tem = new T[n];
		for (unsigned int i = 0; i < size_; ++i)
			tem[i] = data_[(front_ + i) % capacity_];
		delete[] data_;
		data_ = tem;
		capacity_ = n;
		front_ = 0;
		tail_ = size_;
	}

	void push(const T e) {
		if (size_ == capacity_)
			resize(capacity_ * 2);
		data_[tail_] = e;
		tail_ = (tail_ + 1) % capacity_;
		++size_;
	}

	T& pop() {
		if (empty())
			throw std::out_of_range("the queue is empty");

		T e = data_[front_];
		front_ = (front_ + 1) % capacity_;
		--size_;
		if (size_ == capacity_ / 4 && capacity_ > 1)
			resize(capacity_ / 2);
		return e;
	}

	T& operator[](const unsigned int &index) {
		if (index >= size_)
			throw std::out_of_range("queue subscript out of range");
		return data_[(front_ + index) % capacity_];
	}

	T& front() {
		return data_[front_];
	}

	T& back() {
		return data_[tail_ - 1];
	}


	
};
