#pragma once
#include "pch.h"
#include "tree.h"
#include "bureaucracy.h"
#include "queue.cpp" // for bfs traversal

//------------------------------------------------
// constructors:

template <class T>
tree<T>::~tree()
{
	clear();
}

template <class T>
tree<T>::tree(const T& value)
{
	n = 1;
	root = new ptr(value);
}

//------------------------------------------------
// specific methods:

template <class T>
void tree<T>::clear(ptr& parent)
{
	if (parent == nullptr)
		return;
	for (size_t i = 0; i < root->nr_children(); i++)
		clear(root->children[i]);
	delete parent;
	n--;
	parent = nullptr;
}

//------------------------------------------------
// constant methods:

template <class T>
size_t tree<T>::getn() const
{
	return n;
}

template <class T>
void tree<T>::prnt(ptr& parent, const short& traversal_method) const
{
	if (parent == nullptr)
		return;

	switch (traversal_method)
	{
	case bfs:
		queue<node_tree<T>*> nodes = parent;
		while (!nodes.empty())
		{
			int original_size = nodes.get_size();

			// add to queue, action until original_size, and then remove
			FOR(original_size)
			{
				node_tree<T>* node = nodes.front();
				std::cout << node->get() << ' ';				
				FOR(node->nr_children())
					if (node->children[i]) // patch
						nodes.push(node->children[i]);
				nodes.pop();
			}
		}
		break;

	case preorder:
		std::cout << parent->get() << ' ';
		for (size_t i = 0; i < parent->nr_children(); i++)
			prnt(parent->children[i], traversal_method);
		break;
		
	case inorder:
		for (size_t i = 0; i < parent->nr_children() - 1; i++)
			prnt(parent->children[i], traversal_method);
		std::cout << parent->get() << ' ';
		std::cout << parent->children[parent->nr_children() - 1]->get() << ' ';
		break;

	case postorder:
		for (size_t i = 0; i < parent->nr_children(); i++)
			prnt(parent->children[i], traversal_method);
		std::cout << parent->get() << ' ';
		break;
	default:
		break;
	}
}

template <class T>
bool tree<T>::empty() const
{
	return root == nullptr;
}

template <class T>
size_t tree<T>::height(ptr& parent) const
{
	if (parent == nullptr)
		return 0;

	size_t maximum_height = -1;
	FOR(parent->nr_children())
	{
		size_t h = heght(parent->children[i]);
		maximum_height = maximum_height > h ? maximum_height : h;
	}
	return 1 + maximum_height;
}

template <class T>
void* tree<T>::collection_ptr() const
{
	return (void*)root;
}
