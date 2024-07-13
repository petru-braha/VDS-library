#pragma once
#include "pch.h"
#include "special_binary_tree.h"
#include "bureaucracy.h"
#include "queue.cpp" // for bfs traversal

//------------------------------------------------
// constructors:

template <class T, typename node_type>
special_binary_tree<T, node_type>::~special_binary_tree()
{
	clear(root);
	if (this->root == nullptr)
		std::cout << "\nardeee\n";
}

template <class T, typename node_type>
special_binary_tree<T, node_type>::special_binary_tree(const T& value)
{
	n = 1;
	root = new node_type(value);
}

//------------------------------------------------
// specific methods:

template <class T, class node_type>
void special_binary_tree<T, node_type>::clear(node_bint<T>*& parent)
{
	if (parent == nullptr)
		return;
	clear(parent->left);
	clear(parent->rght);
	
	delete parent;
	parent = nullptr;
	if (parent == nullptr)
		std::cout << "\ntrebuie sa arda\n";
	n--;
}
/*
//------------------------------------------------
// constant methods:
/*
template <class T, class node_type>
size_t special_binary_tree<T, node_type>::getn() const
{
	return n;
}

template <class T, class node_type>
void special_binary_tree<T, node_type>::prnt(ptr& parent, const short& traversal_method) const
{
	if (parent == nullptr)
		return;

	switch (traversal_method)
	{
	case bfs:
		queue<node_special_binary_tree<T>*> nodes = parent;
		while (!nodes.empty())
		{
			int original_size = nodes.get_size();

			// add to queue, action until original_size, and then remove
			FOR(original_size)
			{
				node_special_binary_tree<T>* node = nodes.front();
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

template <class T, class node_type>
bool special_binary_tree<T, node_type>::empty() const
{
	return root == nullptr;
}

template <class T, class node_type>
size_t special_binary_tree<T, node_type>::height(ptr& parent) const
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

template <class T, class node_type>
void* collection_ptr(const special_binary_tree<T, node_type>& t) 
{
	return (void*)root;
}
*/