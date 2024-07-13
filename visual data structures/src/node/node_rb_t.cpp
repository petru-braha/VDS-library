#pragma once
#include "pch.h"
#include "node/node_rb_t.h"

template <class T>
node_rb_t<T>::node_rb_t(const T& value, const bool& color) : node_bint<T>(value), color(color) {};

template <class T>
node_rb_t<T>::~node_rb_t() {}

template <class T>
void node_rb_t<T>::set_color(const bool& color)
{
	this->color = color;
}

template <class T>
bool node_rb_t<T>::get_color() const
{
	return this->color;
}
