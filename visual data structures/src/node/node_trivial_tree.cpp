#pragma once
#include "pch.h"
#include "node/node_trivial_tree.h"

template <class T>
node_trivial_tree<T>::node_trivial_tree(const T& value, const size_t& arity) : node<T>(value), arity(arity)
{
	children = new (T*)[arity];
	for (size_t i = 0; i < arity; i++)
		children[i] = nullptr;
}

template <class T>
node_trivial_tree<T>::~node_trivial_tree()
{
	if(children)
		delete[]children;
}

template <class T>
size_t node_trivial_tree<T>::get_arity() const
{
	return this->arity;
}
