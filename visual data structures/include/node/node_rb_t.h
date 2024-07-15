#pragma once
#include "node.h"

template <class T>
class node_rb_t : node<T, node_rb_t<T>, 2>
{
	// data members:
	bool color;
public:
	// constructors:
	node_rb_t(const T& value, const bool& color = NULL);
	~node_rb_t();

	// specific methods:
	void set_color(const bool& color);
	
	// constant methods:
	bool get_color() const;
};

//------------------------------------------------
// constructors:

template <class T>
node_rb_t<T>::~node_rb_t() {}

template <class T>
node_rb_t<T>::node_rb_t(const T& value, const bool& color) : node<T, node_rb_t<T>, 2>(value), color(color) {}

//------------------------------------------------
// specific methods:

template <class T>
void node_rb_t<T>::set_color(const bool& color)
{
	this->color = color;
}

//------------------------------------------------
// constant methods:

template <class T>
bool node_rb_t<T>::get_color() const
{
	return color;
}
