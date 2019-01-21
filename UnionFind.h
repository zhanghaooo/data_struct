#pragma once
#include"Array.h"

class UnionFind {
private:
	Array<int> parents_;

	int find_root(int i)
	{
		int root = i;
		while (parents_[root] != root) {
			root = parents_[root];
		}
		int pre;
		while (i != root) {
			pre = i;
			i = parents_[i];
			parents_[pre] = root;
		}
		return root;
	}

public:
	UnionFind(int n) : parents_(Array<int>(n)) 
	{
		for (int i = 0; i < n; ++i) {
			parents_[i] = i;
		}
	}

	bool is_connected(int i, int j) 
	{
		return find_root(i) == find_root(j);
	}

	void unite(int i, int j)
	{
		parents_[find_root(i)] = find_root(j);
	}

};
