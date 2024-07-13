#pragma once
#include "node/node_bint.cpp"

template <class T>
class node_rb_t : node_bint<T>
{
	// data members:
	bool color;
public:
	// constructors:
	node_rb_t(const T& value = NULL, const bool& color = NULL);
	~node_rb_t();

	// specific methods:
	void set_color(const bool& color);
	bool get_color() const;
};