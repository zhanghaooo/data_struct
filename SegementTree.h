#pragma once
#include<exception>
#include "Vector.h"

template<typename T>
class SegementTree {
	using size_t = unsigned int;
private:
	Vector<T> data_;
	Vector<T> tree_;
	T (*merge_)(const T &e1, const T &e2);

	size_t left_child(size_t index) 
	{
		return 2 * index + 1;
	}

	size_t right_child(size_t index) 
	{	
		return 2 * index + 2;
	}

	void build_segement_tree(size_t index, size_t l, size_t r)
	{	
		if (l >= r)
			return;
		if (l + 1 == r) {
			tree_[index] = data_[l];
			return;
		}
		size_t m = l + (r - l) / 2;
		size_t lc = left_child(index);
		size_t rc = right_child(index);
		build_segement_tree(lc, l, m);
		build_segement_tree(rc, m, r);
		tree_[index] = merge_(tree_[lc], tree_[rc]);
	}

	T query(size_t i, size_t j, size_t index, size_t l, size_t r)
	{
		if (i == l && j == r)
			return tree_[index];
		size_t m = l + (r - l) / 2;
		size_t lc = left_child(index);
		size_t rc = right_child(index);
		if (j <= m)
			return query(i, j, lc, l, m);
		if (i >= m)
			return query(i, j, rc, m, r);
		return merge_(query(i, m, lc, l, m), query(m, j, rc, m, r));
	}

	void set(size_t i, T value, size_t index, size_t l, size_t r)
	{
		if (l >= r)
			return;
		if (l + 1 == r) {
			tree_[index] = value;
			return;
		}
		size_t m = l + (r - l) / 2;
		size_t lc = left_child(index);
		size_t rc = right_child(index);
		if (i < m)
			set(i, value, lc, l, m);
		else
			set(i, value, rc, m, r);
		tree_[index] = merge_(tree_[lc], tree_[rc]);
		return;
	}

public:
	SegementTree(Vector<T> v, T(*merge)(const T &e1, const T &e2))
	{
		data_ = v;
		tree_ = Vector<T>(4 * data_.size());
		merge_ = merge;
		build_segement_tree(0, 0, data_.size());
		//cout << data_ << endl << tree_;
	}

	T query(size_t i, size_t j) 
	{
		if (i < 0 || j > data_.size() || i >= j)
			throw std::out_of_range("query called on empty interval\n");
		return query(i, j, 0, 0, data_.size());
	}

	void set(size_t i, T value)
	{
		if (i < 0 || i >= data_.size())
			throw std::out_of_range("set called on empty interval\n");
		return set(i, value, 0, 0, data_.size());
	}
};