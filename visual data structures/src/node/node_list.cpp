#pragma once
#include "pch.h"
#include "node/node_list.h"

template <class T>
node_list<T>::node_list(const T& value) : node<T>(value), next(nullptr) {}

template <class T>
node_list<T>::~node_list() {}
