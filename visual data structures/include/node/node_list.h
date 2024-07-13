#pragma once
#include "node/node.cpp"

template <class T>
class node_list : public node<T>
{
public:
	// auxiliar utility:
	node_list<T>* next;

	// constructors:
	node_list(const T& value = NULL);
	~node_list();
};
