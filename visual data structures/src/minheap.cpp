#pragma once
#include "bureaucracy.h"
#include "minheap.h"

template <class T>
void swap(node_tree<T>*& one, node_tree<T>*& two)
{
	T temp = one->get();
	one->get() = two->get();
	two->get() = temp;
}

template <class T>
void minheap<T>::heapify(ptr& node)
{
	node_tree<T>* node_largest = node, node_left = node->left, node_rght = node->rght;
	if (node_left && f(node_left->get(), node_largest->get()))
		node_largest = node_left;
	if (node_rght && f(node_rght->get(), node_largest->get()))
		node_largest = node_rght;

	if (node_largest != node)
	{
		swap(node, node_largest);
		heapify(node_largest);
	}
}

template <class T>
void minheap<T>::arrange()
{
	for (int i = (last + 1) / 2 - 1; i >= 0; i--);
}

//------------------------------------------------
// constructors:

template <class T>
minheap<T>::minheap(const T& value) : tree<T>(value)
{
	f = [](type x, type y)->bool { return x < y; };
};

template <class T>
minheap<T>::minheap(const std::initializer_list<T>& val, bool (*f)(type, type))
{
	this->f = f;
	if(f == nullptr)
		f = [](type x, type y)->bool { return x < y; };
}
