#pragma once
#include "pch.h"
#include "trivial_tree.h"

template <class T>
bool trivial_tree<T>::complete(ptr& parent) const
{
	if (parent == nullptr)
		return true;
	bool result = true;

	for (size_t i = 0; i < parent->nr_children() - 1; i++)
	{
		result = (result && complete(parent->children[i], traversal_method);
		if (result == false)
			return false;
	}
	if (complete_individual_check(parent, root->nr_children()) == false)
		return false;
	if (parent->children[parent->nr_children() - 1]->nr_children() != root->nr_children())
		return false;
	return true;
}

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

template <class T>
tree<T>::tree(const std::initializer_list<T>& val, const short& traversal_method = bfs)
{

}

//tree(T* val, const short& traversal_method = bfs);

template <class T>
tree<T>::tree(const tree<T>& t)
{
	if (t.root == nullptr)
		return;

	root = new ptr(t.root->get(), t.root->nr_children());
	queue<node_tree<T>*> nodes = root;
	queue<node_tree<T>*> nodes_t = t.root;
	while (!nodes_t.empty())
	{
		int original_size = nodes_t.get_size();

		// add to queue, action until original_size, and then remove
		FOR(original_size)
		{
			node_tree<T>* node = nodes.front();
			node_tree<T>* node_t = nodes_t.front();
			FOR(node->nr_children())
			{
				if (node_t->children[i] == nullptr)
					node->children[i] = nullptr;
				else
				{
					T value = node_t->children[i]->get();
					short arity = node_t->children[i]->nr_children();
					node->children[i] = new ptr(value, arity);
				}
				if (node_t->children[i])
				{
					nodes.push(node->children[i]);
					nodes_t.push(node_t->children[i]);
				}
			}
			nodes.pop();
		}
	}
}

template <class T>
tree<T>::tree(const tree<T>&& t)
{
	if (t.root == nullptr)
		return;

	root = new ptr(t.root->get(), t.root->nr_children());
	queue<node_tree<T>*> nodes = root;
	queue<node_tree<T>*> nodes_t = t.root;
	while (!nodes_t.empty())
	{
		int original_size = nodes_t.get_size();

		// add to queue, action until original_size, and then remove
		FOR(original_size)
		{
			node_tree<T>* node = nodes.front();
			node_tree<T>* node_t = nodes_t.front();
			FOR(node->nr_children())
			{
				if (node_t->children[i] == nullptr)
					node->children[i] = nullptr;
				else
				{
					T value = node_t->children[i]->get();
					short arity = node_t->children[i]->nr_children();
					node->children[i] = new ptr(value, arity);
				}
				if (node_t->children[i])
				{
					nodes.push(node->children[i]);
					nodes_t.push(node_t->children[i]);
				}
			}
			nodes.pop();
		}
	}

	t.clear();
}

//------------------------------------------------
// specific methods:

template <class T>
tree<T>& tree<T>::operator = (const tree<T>& t)
{
	if (this->get_arity(root) != t.get_arity(t.root))
	{
		eazy_error("incompatible data");
		return *this;
	}

	delete* this;
	return *this = new tree<T>(t);
}

template <class T>
void tree<T>::clear(ptr& parent)
{
	if (parent == nullptr)
		return;
	for (size_t i = 0; i < root->nr_children(); i++)
		clear(root->children[i]);
	delete parent;
	parent = nullptr;
}

template <class T>
void tree<T>::insert(const T& value)
{
	if (root == nullptr)
	{
		root = new ptr(value);
		return;
	}

	queue<node_tree<T>*> nodes = root;
	while (!nodes.empty())
	{
		int original_size = nodes.get_size();

		// add to queue, action until original_size, and then remove
		FOR(original_size)
		{
			node_tree<T>* node = nodes.front();
			FOR(node->nr_children())
			{
				if (node->children[i] == nullptr)
				{
					node->children[i] = new ptr(value);
					return;
				}
				nodes.push(node->children[i]);
			}
			nodes.pop();
		}
	}
}

template <class T>
void tree<T>::remove(const T& value, ptr& parent)
{
	if (parent == nullptr)
		return;
	if (parent->get() == value)
	{
		delete parent;
		parent = nullptr;
		n--;
		this->get_arity(); // recalculate arity
		return;
	}

	FOR(parent->nr_children())
		remove(value, parent->children[i]);
}

template <class T>
node_tree<T>* tree<T>::search(const T& value, ptr& parent) const
{
	if (parent == nullptr)
		return nullptr;
	if (parent->get() == value)
		return parent;

	ptr pointer_child = nullptr;
	FOR(parent->nr_children())
	{
		ptr temp_ptr = search(value, parent->children[i]);
		pointer_child = temp_ptr == nullptr ? pointer_child : temp_ptr;
	}

	return pointer_child;
}

//------------------------------------------------
// constant methods:

template <class T>
bool tree<T>::operator == (const tree<T>& t)
{
	if (this->n != t.n || this->get_arity() != t.get_arity())
		return false;
	if (root == nullptr && t.root == nullptr)
		return true;

	queue<node_tree<T>*> nodes = root;
	queue<node_tree<T>*> nodes_t = t.root;

	while (!nodes.empty())
	{
		int original_size = nodes.get_size();

		// check for the pointer itself and also for their values
		FOR(original_size)
		{
			node_tree<T>* node1 = nodes.front();
			node_tree<T>* node2 = nodes_t.front();

			if ((node1 == nullptr && node2) || (node1 && node2 == nullptr))
				return false;
			if (node1)  // if both aren't nullptr
				if (node1->get() != node2->get())
					return false;

			FOR(node->nr_children())
			{
				if (node1->children[i] && node2->children[i]) // patch
				{
					nodes.push(node1->children[i]);
					nodes_t.push(node2->children[i]);
				}
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
short tree<T>::get_arity(ptr& parent) const
{
	if (parent == nullptr)
		return 0;

	short maximum = -1;
	FOR(parent->nr_children() - 1)
	{
		short temp = get_arity(parent->children[i]);
		maximum = maximum < temp ? temp : maximum;
	}

	maximum = maximum < parent->nr_children() ? parent->nr_children() : maximum;
	ptr temp = parent->children[i]->nr_children();
	maximum = maximum < temp ? temp : maximum;
	return maximum;
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


