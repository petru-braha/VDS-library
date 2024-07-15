#pragma once
#include "node.h"

template <class T>
class node_bint : public node<T, node_bint<T>, 2>
{
public:
	// constructors:
	~node_bint();
	node_bint(const T& value);
};

//------------------------------------------------
// constructors:

template <class T>
node_bint<T>::~node_bint() {}

template <class T>
node_bint<T>::node_bint(const T& value) : node<T, node_bint<T>, 2>(value) {}
