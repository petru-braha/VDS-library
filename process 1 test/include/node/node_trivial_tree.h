#pragma once
#include "node.h"

template <class T>
class node_trivial_tree : public node<T>
{
	// data members:
	size_t arity;
public:
	// auxiliar utility:
	node_trivial_tree<T>** children;

	// constructors:
	node_trivial_tree(const T& val, const size_t& arity);
	~node_trivial_tree();

	// specific methods:
	size_t get_arity() const;
};

//------------------------------------------------
// constructors:

template <class T>
node_trivial_tree<T>::~node_trivial_tree()
{
	if (children)
		delete[]children;
}

template <class T>
node_trivial_tree<T>::node_trivial_tree(const T& value, const size_t& arity) : node<T>(value), arity(arity)
{
	children = new (T*)[arity];
	for (size_t i = 0; i < arity; i++)
		children[i] = nullptr;
}

//------------------------------------------------
// specific methods:

template <class T>
size_t node_trivial_tree<T>::get_arity() const
{
	return this->arity;
}
