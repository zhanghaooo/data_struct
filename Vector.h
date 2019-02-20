#pragma once
#include<exception>
#include<ostream>
#include"Array.h"

template<typename T>
class Vector {
	using size_t = unsigned int;

private:
	size_t size_;
	Array<T> data_;

	void resize(const size_t &size) 
	{
		Array<T> data(size);
		size_ = (size < size_) ? size : size_;
		for (size_t i = 0; i < size_; ++i) {
			data[i] = data_[i];
		}
		swap(data_, data);
	}

public:
	Vector() : size_(0), data_(0) {}

	Vector(const size_t &size) : size_(size), data_(Array<T>(size)) {}
    
	Vector(const size_t &size, const T &value) : size_(size), data_(Array<T>(size, value)) {}

	Vector(std::initializer_list<T> il) : Vector((size_t)il.size())
	{
		auto it = il.begin();
		for (int i = 0; i < il.size(); ++i) {
			data_[i] = *it;
			++it;
		}
	}

	//copy-assignment operator
	Vector<T>& operator = (const Vector<T> &v) 
	{
		if (this == &v)
			return *this;
		size_ = v.size_;
		data_ = v.data_;
		return *this;
	}

	size_t size() 
	{
		return size_;
	}

	size_t capacity() 
	{
		return (size_t)data_.size();
	}

	bool empty() 
	{
		return size_ == 0;
	}

	void clear() 
	{
		size_ = 0;
	}

	void insert(const size_t &index, const T e) 
	{
		if (index > size_)
			throw std::out_of_range("Vector subscript out of range");
		if (size_ == data_.size() && size_ > 0)
			resize(data_.size() * 2);
		else
			resize(1);
		for (size_t i = size_; i > index; --i)
			data_[i] = data_[i - 1];
		data_[index] = e;
		++size_;
	}

	void push_back(const T e) 
	{
		insert(size_, e);
	}

	void erase(const size_t &index) 
	{
		if (index >= size_)
			throw std::out_of_range("Vector subscript out of range\n");
		for (size_t i = index; i < size_ - 1; ++i)
			data_[i] = data_[i + 1];
		--size_;
		if (size_ == data_.size() / 4 && data_.size() > 1)
			resize(data_.size() / 2);
	}

	T pop_back() 
	{
		if (empty())
			throw std::out_of_range("pop_back() called on empty Vector\n");
		T back = data_[size_ - 1];
		erase(size_ - 1);
		return back;
	}

	T front() 
	{
		if (size_ == 0)
			throw std::out_of_range("front() called on empty Vector\n");
		return data_[0];
	}

	T back() 
	{
		if (size_ == 0)
			throw std::out_of_range("back() called on empty Vector\n");
		return data_[size_ - 1];
	}

	T& operator [] (const size_t &index) 
	{
		if (index >= size_)
			throw std::out_of_range("Vector subscript out of range\n");
		return data_[index];
	}

	const T& operator [] (const size_t &index) const 
	{
		if (index >= size_)
			throw std::out_of_range("Vector subscript out of range\n");
		return data_[index];
	}

	size_t find(const T &e) 
	{
		for (size_t i = 0; i < size_; ++i) {
			if (data_[i] == e)
				return i;
		}
		return size_;
	}

	size_t count(const T &e) 
	{
		size_t n = 0;
		for (size_t i = 0; i < size_; ++i) {
			if (data_[i] == e)
				++n;
		}
		return n;
	}

	void reverse() 
	{
		using std::swap;
		for (size_t i = 0; i < size_ / 2; ++i) {
			swap(data_[i], data_[size_ - 1 - i]);
		}
	}

	friend std::ostream &operator << (std::ostream &os, const Vector<T> &v)
	{
		os << v.data_;
		return os;
	}

	friend bool operator == (const Vector<T> &v1, const Vector<T> &v2)
	{
		if (v1.size_ != v2.size_)
			return false;
		for (size_t i = 0; i < v1.size_; ++i) {
			if (v1[i] != v2[i])
				return false;
		}
		return true;
	}

	friend void swap(const Vector<T> &v1, const Vector<T> &v2) 
	{
		using std::swap;
		swap(v1.size_, v2.size_);
		swap(v1.data_, v2.data_);
	}
};