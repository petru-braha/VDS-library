#pragma once
#include "node.h"

template <class T = int>
class node_list : public node<T>
{
public:
	node_list<T>* next;
	node_list(const T& val = NULL) : node<T>(val), next(nullptr) {}
	~node_list() {}
};
