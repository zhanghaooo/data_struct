#pragma once
#include"Vector.h"

template<typename T>
class Heap {
	using size_t = unsigned int;
private:
	bool(*cmp_)(const T &e1, const T &e2) = [](const T &e1, const T &e2) {return e1 < e2; };
	Vector<T> data_;

	size_t parent(size_t index) 
	{
		return (index - 1) / 2;
	}

	size_t left_child(size_t index) 
	{
		return index * 2 + 1;
	}

	size_t right_child(size_t index) 
	{
		return index * 2 + 2;
	}

	void sift_up(size_t k) 
	{
		while (k > 0 && !cmp_(data_[parent(k)], data_[k])) {
			swap(data_[k], data_[parent(k)]);
			k = parent(k);
		}
	}

	void sift_down(size_t k) 
	{
		while (left_child(k) < data_.size()) {
			int child = left_child(k);
			if (right_child(k) < data_.size() && !cmp_(data_[left_child(k)], data_[right_child(k)]))
				child = right_child(k);
			if (cmp_(data_[k], data_[child])) 
				break;
			swap(data_[k], data_[child]);
			k = child;
		}
	}

public:
	Heap() = default;

	Heap(bool(*cmp)(const T &e1, const T &e2)): cmp_(cmp) {};

	Heap(Vector<T> v): data_(v)
	{
  		for (size_t i = parent(v.size() - 1); i < v.size(); --i)
			sift_down(i);
	}

	Heap(Vector<T> v, bool(*cmp)(const T &e1, const T &e2)) : cmp_(cmp), data_(v) 
	{
		for (size_t i = parent(v.size() - 1); i < v.size(); --i)
			sift_down(i);
	}

	bool empty()
	{
		return data_.empty();
	}

	size_t size()
	{
		return data_.size();
	}

	void push(T e) 
	{
		data_.push_back(e);
		sift_up(data_.size() - 1);
	}

	T pop() 
	{
		T e = top();
		swap(data_[0], data_[data_.size() - 1]);
		data_.pop_back();
		sift_down(0);
		return e;
	}

	T top() 
	{
		return data_[0];
	}

	T replace(const T e) 
	{
		T top_e = top();
		data_[0] = e;
		sift_down(0);
		return top_e;
	}
};