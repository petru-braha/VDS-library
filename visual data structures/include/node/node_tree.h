#pragma once
#include "node.h"

#define left_child 0
#define rght_child 1
typedef unsigned long long int ull;

template <class T = int>
class node_tree : public node<T>
{
public:
	node_tree<T>** children;
	// malloc n + 1 s.t. when iterating through children, last position is nullptr => we know we have to stop

	node_tree(const T& val = NULL, const size_t& nr_children = 2) : node<T>(val)
	{
		children = new node_tree<T>*[nr_children + 1];
		for (size_t i = 0; i < nr_children + 1; i++)
			children[i] = nullptr;
	}
	~node_tree() {}

	size_t nr_children() const { size_t i = 0; for (; children[i] == nullptr; i++); for (; children[i]; i++); return i; }
};
