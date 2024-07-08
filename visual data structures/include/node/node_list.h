#pragma once
#include "node.h"

template <class T>
class node_list : public node<T>
{
	T data;
public:
	node_list<T>* next;
	
	node_list() : data(NULL), next(nullptr) {};
	node_list(const T& val) : data(val), next(nullptr) {};
	
	void set(const T& data) { this->data = data; }
	T    get() const { return data; };
};
