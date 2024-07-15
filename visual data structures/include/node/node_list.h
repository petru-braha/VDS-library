#pragma once
#include "node.h"

template <class T>
class node_list : public node<T, node_list<T>, 1>
{
public:
	// constructors:
	node_list(const T& value);
	~node_list();
};

//------------------------------------------------
// constructors:

template <class T>
node_list<T>::~node_list() {}

template <class T>
node_list<T>::node_list(const T& value) : node<T, node_list<T>, 1>(value) {}
