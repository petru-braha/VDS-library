#pragma once
#include "pch.h"
#include "node/node_avlt.h"

template <class T>
node_avlt<T>::node_avlt(const T& value) : node_bint<T>(value), height(0) {}

template <class T>
node_avlt<T>::~node_avlt(){}

template <class T>
void node_avlt<T>::set_height(const size_t& value)
{
	this->height = value;
}

template <class T>
T& node_avlt<T>::get_height() const
{
	return this->height;
}
