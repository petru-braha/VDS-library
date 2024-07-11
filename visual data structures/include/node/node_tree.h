#pragma once
#include "node.h"

// definitions:
#define red 0
#define blk 1

typedef const bool elemental;
typedef const char red_black;

// binary node for the tree class itself:
template <class T = int, class node_type = elemental>
class node_tree : public node<T>
{
public:
	node_tree<T>* left;
	node_tree<T>* rght;

	node_tree(const T& val = NULL) : node<T>(val), left(nullptr), rght(nullptr) {}
	~node_tree() {}
};

template <class T>
class node_tree<T, red_black> : public node_tree<T, elemental>
{
public:
	bit color;
};
