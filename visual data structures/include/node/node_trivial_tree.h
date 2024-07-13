#pragma once
#include "node/node.cpp"

template <class T>
class node_trivial_tree : public node<T>
{
	// data members:
	size_t arity;
public:
	// auxiliar utility:
	node_trivial_tree<T>** children;

	// constructors:
	node_trivial_tree(const T& val = NULL, const size_t& arity = 2);
	~node_trivial_tree();

	// specific methods:
	size_t get_arity() const;
};
