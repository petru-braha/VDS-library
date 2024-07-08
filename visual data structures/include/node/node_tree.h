#pragma once
#include "node.h"

#define left_child 0
#define rght_child 1
typedef unsigned long long int ull;

template <class T, ull nr_nodes = 2>
class node_tree : public node<T>
{
	T data;
public:
	node<T>* children[nr_nodes];

	node_tree(const T& val = NULL) : data(val) { for (size_t i = 0; i < nr_nodes; i++) children[i] = nullptr; }

	void set(const T& data) { this->data = data; }
	T    get() const { return data; }
};