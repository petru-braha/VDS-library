#pragma once
#include "node.h"

// auxiliar utility:
template <class T>
class node_double_list : public node<T, node_double_list<T>, 1>
{
public:
	// auxiliar utility:
	// node_type* successor[arity];
	node_type* predecessor[arity];

	// constructors:
	~node_double_list();
	node_double_list(const T& value = NULL);
};

//------------------------------------------------
// constructors:

template <class T>
node_double_list<T>::~node_double_list() {}

template <class T>
node_double_list<T>::node_double_list(const T& value) : node<T, node_double_list<T>, 1>(value)
{
	this->predecessor[0] = nullptr;
}
