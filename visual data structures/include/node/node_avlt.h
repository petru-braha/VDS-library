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
	node_avlt(const T& value);

	// specific methods:
	void set_height(const size_t& value);
	
	// constant methods:
	size_t get_height() const;
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
