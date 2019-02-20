#pragma once
#include<exception>
#include<ostream>
#include<initializer_list>

template<typename T>
class Array {
	using size_t = unsigned int;
private:
	size_t size_;
	T *data_;

public:
	Array(const size_t &size) : size_(size), data_(new T[size]) {}

	Array(const size_t &size, const T &value) : size_(size), data_(new T[size])
	{
		for (size_t i = 0; i < size; ++i) {
			data_[i] = value;
		}
	}

	Array(std::initializer_list<T> il): Array((size_t)il.size())
	{
		auto it = il.begin();
		for (int i = 0; i < il.size(); ++i) {
			data_[i] = *it;
			++it;
		}
	}

	//copy constructor
	Array(const Array<T> &array) : size_(array.size_), data_(new T[array.size_])
	{
		for (size_t i = 0; i < array.size_; ++i) {
			data_[i] = array.data_[i];
		}
	}

	//copy-assignment operator
	Array<T>& operator = (const Array<T> &array)
	{
		if (size_ > 0) {
			delete[] data_;
		}
		size_ = array.size_;
		data_ = new T[size_];
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = array.data_[i];
		}
		return *this;
	}

	//destruct
	~Array()
	{
		delete[] data_;
		data_ = nullptr;
	}

	T& operator [] (const size_t &index)
	{
		if (index >= size_) {
			throw std::out_of_range("Array subscript out of range\n");
		}
		return data_[index];
	}

	const T& operator [] (const size_t &index) const
	{
		if (index >= size_) {
			throw std::out_of_range("Array subscript out of range\n");
		}
		return data_[index];
	}

	size_t size()
	{
		return size_;
	}

	T front()
	{
		if (size_ == 0) {
			throw std::out_of_range("front() called on empty Array\n");
		}
		return data_[0];
	}

	T back()
	{
		if (size_ == 0) {
			throw std::out_of_range("back() called on empty Array\n");
		}
		return data_[size_ - 1];
	}

	friend bool operator == (const Array<T> &array1, const Array<T> &array2) 
	{
		if (array1.size_ != array2.size_) {
			return false;
		}
		for (size_t i = 0; i < array1.size_; ++i) {
			if (array1.data_[i] != array2.data_[i])
				return false;
		}
		return true;
	}

	friend std::ostream &operator << (std::ostream &os, const Array<T> &array)
	{
		for (size_t i = 0; i < array.size_; ++i) {
			os << array.data_[i] << " ";
		}
		return os;
	}

	friend void swap(Array<T> &array1, Array<T> &array2)
	{
		using std::swap;
		swap(array1.size_, array2.size_);
		swap(array1.data_, array2.data_);
	}
};