#pragma once
#include "bureaucracy.h"

#include "../class_methods/abstract class methods.h/modifier_methods.h"
#include "../class_methods/avl_methods/avl_specific.h"
#include "../class_methods/avl_methods/avl_constant.h"
#include "../class_methods/avl_methods/avl_queries.h"
#include "../class_methods/abstract class methods.h/instance_synergy.h"
#include "../class_methods/abstract class methods.h/iterator_methods.h"

#include "iterators/avl_iterator.h"

#include "node/node_avlt.h"
#include "data_structure.h"
#include <initializer_list>

/* comments:
	- unstable iterator
*/

template <class T = int>
class avl : public data_structure<modifier_methods<T, avl<T>>, avl_specific<node_avlt<T>>,
	avl_constant<avl<T>, node_avlt<T>>, avl_queries<T, node_avlt<T>>, 
	instance_synergy<avl<T>>, iterator_methods<avl_iterator<T>>>
{
	// typedefs:
	structure_typedefs;
	typedef node_avlt<T>* ptr;
	typedef const node_avlt<T>* ptr_return;

public:
	// constructors:
	~avl();
	avl();
	avl(const std::initializer_list<T>& data);
	avl(const T* data, szt data_size);
	avl(const avl<T>& tree);
	avl(const avl<T>&& tree);

	// modifier methods:
	avl<T>& operator = (const avl<T>& t);
	avl<T>& clear();
	avl<T>& setf(fct f);

	// specific methods:
	ptr insert(ptr& parent, const node_avlt<T>* const value);
	ptr remove(ptr& parent, const node_avlt<T>* const value);

	// constant methods:
	bool operator == (const avl<T>& t) const;
	size_t get_n() const;
	void*  get_f() const;
	bool   empty() const;
	void   print() const;
	size_t get_arity() const;
	ptr_return get_r() const;
	
	// query operations:
	size_t height(const node_avlt<T>* const parent) const;
	ptr_return search(const node_avlt<T>* parent, t value) const;
	ptr_return minimum() const;
	ptr_return maximum() const;
	ptr_return predcessr(const node_avlt<T>* value) const;
	ptr_return successor(const node_avlt<T>* value) const;

	// instance synergy:
	avl<T>& integrates(const avl<T>& arr);
	avl<T>& eliminates(const avl<T>& arr);
	avl<T>& intersects(const avl<T>& arr);

	// iterator methods:
	avl_iterator<T> begin() const;
	avl_iterator<T> end() const;

	// friend functions:
	template <class T> friend T* convert(const avl<T>& t);
	template <class T> friend std::ostream& operator << (std::ostream& out, const avl<T>& t);

private:
	// data members:
	node_avlt<T>* root;
	size_t n;

	// auxiliar utility:
	static const size_t left;
	static const size_t rght;

	fct compare;
	ptr left_rotation(ptr& node);
	ptr rght_rotation(ptr& node);
	bit balnce_factor(const ptr& node) const;
};

//------------------------------------------------
// constructors:

template <class T>
avl<T>::~avl() 
{ 
	clear(); 
}

template <class T>
avl<T>::avl()
{
	root = nullptr;
	n = 0;
	compare = [](t x, t y)-> bool { return x > y; };
}

//------------------------------------------------
// specific methods:

/*
template <class T>
node_avlt<T>* avl<T>::insert_call(ptr& parent, const T& value)
{
	// base case
	if (parent == nullptr)
		return parent = new ptr(value);

	if (value == parent->get())
		return parent;
	// recursive calls
	if (value < parent->get())
		parent->successor[left_child] = insert_call(parent->successor[left_child], value);
	else
		parent->successor[rght_child] = insert_call(parent->successor[rght_child], value);

	// balance factor
	bit balance_factor = balnce_factor(parent);

	// rebalancing
	if (balance_factor > 1 && value < parent->successor[left_child]->get())
		return rght_rotation(parent);
	if (balance_factor < -1 && value > parent->successor[rght_child]->get())
		return left_rotation(parent);

	if (balance_factor > 1 && value > parent->successor[left_child]->get())
	{
		parent->successor[left_child] = left_rotation(parent->successor[left_child]);
		return rght_rotation(parent);
	}

	if (balance_factor < -1 && value < parent->successor[rght_child]->get())
	{
		parent->successor[rght_child] = rght_rotation(parent->successor[rght_child]);
		return left_rotation(parent);
	}

	return parent;
}

template <class T>
node_avlt<T>* avl<T>::remove_call(ptr& parent, const T& value)
{
	// base case
	if (parent == nullptr)
		return parent;

	// searching for the value
	if (value < parent->get())
		parent->successor[left_child] = remove_call(parent->successor[left_child], value);
	else if (value > parent->get())
		parent->successor[rght_child] = remove_call(parent->successor[rght_child], value);

	else // found the value
	{
		// no children
		if (parent->successor[left_child] == nullptr && parent->successor[rght_child] == nullptr)
		{
			delete parent;
			parent = nullptr;
		}
		if (parent->successor[left_child])
		{
			// has both children
			if (parent->successor[rght_child])
			{
				ptr s = parent->successor[rght_child];
				while (s->successor[left_child])
					s = s->successor[left_child];
				parent->set(s->get());
				parent->successor[rght_child] = remove_call(parent->successor[rght_child], parent->successor[rght_child]->get());
			}

			// has only left_child
			else
			{
				parent->set(parent->successor[left_child]->get());
				parent->successor[left_child] = parent->successor[left_child]->successor[left_child];
				parent->successor[rght_child] = parent->successor[left_child]->successor[rght_child];
				delete left;
			}
		}

		// has only rght_child
		else
		{
			parent->set(rght->get());
			parent->successor[left_child] = parent->successor[rght_child]->successor[left_child];
			parent->successor[rght_child] = parent->successor[rght_child]->successor[rght_child];
			delete rght;
		}
	}

	if (parent == nullptr)
		return nullptr;
	size_t h1 = height(left), h2 = height(rght);
	parent->set_height(1 + h1 > h2 ? h1 : h2);

	// balance factor
	bit balance_factor = balnce_factor(parent);
	ptr left = parent->successor[left_child];
	ptr rght = parent->successor[rght_child];

	// rebalancing
	if (balance_factor > 1 && balance_factor(left) >= 0)
		rght_rotation(parent);
	if (balance_factor < -1 && balance_factor(rght) <= 0)
		left_rotation(parent);

	if (balance_factor > 1 && balance_factor(left) < 0)
	{
		parent->successor[left_child] = left_rotation(parent->successor[left_child]);
		rght_rotation(parent);
	}

	if (balance_factor < -1 && balance_factor(rght) > 0)
	{
		parent->successor[rght_child] = lrght_rotation(parent->successor[rght_child]);
		left_rotation(parent);
	}
}*/


//------------------------------------------------
// constant methods:

//------------------------------------------------
// query operations:

template <class T>
size_t avl<T>::height(const node_avlt<T>* const parent) const
{
	return parent->get_height();
}

template <class T>
const node_avlt<T>* avl<T>::search(const node_avlt<T>* parent, t value) const
{
	ptr it = root;
	while (it)
	{
		if (value == it->get())
			return it;
		if (compare(it->get(), value))
			it = it->successor[left_child];
		else
			it = it->successor[rght_child];
	}

	return nullptr; // the value does not exist
}

template <class T>
const node_avlt<T>* avl<T>::minimum() const
{
	ptr it = root;
	while(it->successor[left_child])
		it = it->successor[left_child];
	return it;
}

template <class T>
const node_avlt<T>* avl<T>::maximum() const
{
	ptr it = root;
	while (it->successor[rght_child])
		it = it->successor[rght_child];
	return it;
}

template <class T>
const node_avlt<T>* avl<T>::predcessr(const node_avlt<T>* value) const
{
	ptr it = root;
	while (compare(it->get(), value->get())) // until it points to a value smaller than value->get()
	{
		if (nullptr == it->successor[left_child])
			return nullptr;
		it = it->successor[left_child];
	}

	while (it->successor[rght_child])
	{
		if (compare(value->get(), it->successor[rght_child]))
			it = it->successor[rght_child];
		else
		{
			if (nullptr == it->successor[left_child])
				break;
			it = it->successor[left_child];
		}
	}

	return it;
}

template <class T>
const node_avlt<T>* avl<T>::successor(const node_avlt<T>* value) const
{
	ptr it = root;
	while (compare(value->get(), it->get()))
	{
		if (nullptr == it->successor[rght_child])
			return nullptr;
		it = it->successor[rght_child];
	}

	while (it->successor[left_child])
	{
		if (it->successor[left_child] < value)
			it = it->successor[left_child];
		else
		{
			if (it->successor[rght_child] == nullptr)
				break;
			it = it->successor[rght_child];
		}
	}
}

//------------------------------------------------
// instance synergy:

//------------------------------------------------
// iterator methods:



//------------------------------------------------
// friend functions:


//------------------------------------------------
// auxiliar utility:

template <class T>
const size_t avl<T>::left = 0;

template <class T>
const size_t avl<T>::rght = 0;

template <class T>
node_avlt<T>* avl<T>::left_rotation(ptr& node)
{
	ptr it = node->successor[rght_child];
	node->successor[rght_child] = it->successor[left_child];
	it->successor[left_child] = node;

	size_t h1 = node->successor[left_child]->get_height();
	size_t h2 = node->successor[rght_child]->get_height() + 1;
	node->set_height(h1 > h2 ? h1 : h2);

	h1 = it->successor[left_child]->get_height();
	h2 = it->successor[rght_child]->get_height() + 1;
	it->set_height(h1 > h2 ? h1 : h2);
	return it;
}

template <class T>
node_avlt<T>* avl<T>::rght_rotation(ptr& node)
{
	ptr it = node->successor[left_child];
	node->successor[left_child] = it->successor[rght_child];
	it->successor[rght_child] = node;

	size_t h1 = node->successor[left_child]->get_height();
	size_t h2 = node->successor[rght_child]->get_height() + 1;
	node->set_height(h1 > h2 ? h1 : h2);

	h1 = it->successor[left_child]->get_height();
	h2 = it->successor[rght_child]->get_height() + 1;
	it->set_height(h1 > h2 ? h1 : h2);
	return it;
}

template <class T>
bit avl<T>::balnce_factor(const ptr& node) const
{
	return node->successor[left_child]->get_height() - node->successor[rght_child]->get_height();
}
