#pragma once
#include "node/node.cpp"

#define left_child 0
#define rght_child 1

template <class T>
class node_bint : public node<T>
{
public:
	// auxiliar utility:
	node_bint<T>* left;
	node_bint<T>* rght;

	// constructors:
	node_bint(const T& value = NULL);
	virtual ~node_bint();
};
