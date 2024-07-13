#pragma once
#include "pch.h"
#include "node/node_bint.h"

template <class T>
node_bint<T>::node_bint(const T& value) : node<T>(value)
{
	left = rght = nullptr;
}

template <class T>
node_bint<T>::~node_bint(){}