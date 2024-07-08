#pragma once
#include "node.h"

typedef unsigned long long int ull;

template <class T, ull nr_nodes>
class node_tree : public node<T>
{
	T data;
public:
	node_tree* children[nr_nodes];

	node_tree() : data(NULL) { for (size_t i = 0; i < nr_nodes; i++) children[i] = nullptr; }
	node_tree(const T& val) : data(NULL) { for (size_t i = 0; i < nr_nodes; i++) children[i] = nullptr; }

	void set(const T& data) { data = data; }
	T    get() const { return data; }
};