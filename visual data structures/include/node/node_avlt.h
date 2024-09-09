#pragma once
#include "node.h"

template <class T>
class node_avlt : public node<T, node_avlt<T>, 2>
{
	// data members:
	size_t height;
public:
	// constructors:
	~node_avlt();
	node_avlt(const T& value = NULL);

	// specific methods:
	void set_height(const size_t& value);
	
	// constant methods:
	size_t get_height() const;
	int balance_factor() const;
};

//------------------------------------------------
// constructors:

template <class T>
node_avlt<T>::~node_avlt() {}

template <class T>
node_avlt<T>::node_avlt(const T& value) : node<T, node_avlt<T>, 2>(value), height(0) {}

//------------------------------------------------
// specific methods:

template <class T>
void node_avlt<T>::set_height(const size_t& value)
{
	height = value;
}

//------------------------------------------------
// constant methods:

template <class T>
size_t node_avlt<T>::get_height() const
{
	return height;
}

template <class T>
int node_avlt<T>::balance_factor() const
{
	int val1 = successor[left_child] ? successor[left_child]->get_height() : 0;
	int val2 = successor[rght_child] ? successor[rght_child]->get_height() : 0;
	return val1 - val2;
}
