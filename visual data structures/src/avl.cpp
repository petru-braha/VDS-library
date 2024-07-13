#pragma once
#include "pch.h"
#include "avl.h"


//------------------------------------------------
// auxiliar methods:


//------------------------------------------------
// constructors:

template <class T>
avl<T>::avl(const T& value) : special_binary_tree<T, node_avlt<T>>(value) {}

template <class T>
avl<T>::~avl() {}