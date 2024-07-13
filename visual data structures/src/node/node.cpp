#pragma once
#include "pch.h"
#include "node/node.h"

template <class T>
node<T>::node(const T& value)
{
	this->data = value;
}

template <class T>
T& node<T>::get() const
{
	return (T&)data;
}
