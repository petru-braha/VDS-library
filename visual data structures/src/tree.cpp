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
tree<T>::tree()
{
	root = new ptr;
}

//------------------------------------------------
// specific methods:

template <class T>
tree<T>& tree<T>::operator = (const tree<T>& t)
{
	if (this->arity != t.arity)
	{
		eazy_error("incompatible data");
		return *this;
	}

	delete* this;
	return *this = new tree<T>(t);
}

template <class T>
void tree<T>::clear(ptr& node)
{
	if (node == nullptr)
		return;
	for (size_t i = 0; i < root->nr_children(); i++)
		clear(root->children[i]);
	delete node;
	node = nullptr;
}

template <class T>
void tree<T>::insert(const T& value)
{

}


template <class T>
void tree<T>::remove(const T& value)
{

}

template <class T>
node_tree<T>* tree<T>::search(const T& value) const
{

}



//------------------------------------------------
// constant methods:

template <class T>
bool tree<T>::operator == (const tree<T>& t)
{
	if (this->n != t.n || this->arity != t.arity)
		return false;
	
	queue<node_tree<T>*> nodes = root;
	queue<node_tree<T>*> nodes_t = t.root;
	
	while (!nodes.empty())
	{
		int original_size = nodes.get_size();
		
		// check for the pointer itself
		FOR(original_size)
		{
			node_tree<T>* node1 = nodes.front();
			node_tree<T>* node2 = nodes_t.front();
			
			if ((node1 == nullptr && node2) || (node1 && node2 == nullptr))
				return false;
			if (node1->get() != node2->get())
				return false;

			FOR(node->nr_children())
			{
				nodes.push(node1->children[i]);
				nodes_t.push(node2->children[i]);
			}
			nodes.pop();
			nodes_t.pop();
		}
	}

	return true;
}

template <class T>
size_t tree<T>::getn() const
{
	return n;
}

template <class T>
short tree<T>::get_arity() const
{
	return arity;
}

template <class T>
void tree<T>::prnt(ptr& parent, const short& traversal_method) const
{
	if (parent == nullptr)
		return;

	switch (traversal_method)
	{
	case bfs:
		queue<node_tree<T>*> nodes = root;
		while (!nodes.empty())
		{
			int original_size = nodes.get_size();

			// add to queue, action until original_size, and then remove
			FOR(original_size)
			{
				node_tree<T>* node = nodes.front();
				std::cout << node->get() << ' ';				
				FOR(node->nr_children())
					nodes.push(node->children[i]);
				nodes.pop();
			}
		}

		return true;

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
	// base cases
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
