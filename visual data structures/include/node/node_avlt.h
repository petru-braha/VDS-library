#pragma once
#include "pch.h"
#include "node/node_bint.cpp"

template <class T>
class node_avlt : public node_bint<T>
{
	// data members:
	size_t height;
public:
	// constructors:
	node_avlt(const T& value = NULL);
	~node_avlt();

	// specific methods:
	void set_height(const size_t& value);
	T&   get_height() const;
};
