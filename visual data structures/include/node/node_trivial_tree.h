#pragma once
#include "node.h"

template <class T = int>
class node_trivial_tree : public node<T>
{
	bit arity;
public:
	node_trivial_tree<T>** children;

	// constructors:
	node_trivial_tree(const T& val = NULL, const size_t& arity = 2) : node<T>(val), arity(arity)
	{
		children = new node_tree<T>*[arity];
		for (size_t i = 0; i < arity; i++)
			children[i] = nullptr;
	}

	~node_trivial_tree() {}

	// constant methods:
	size_t get_arity() const { return this->arity; }
};
