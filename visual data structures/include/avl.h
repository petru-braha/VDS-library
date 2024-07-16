#pragma once
#include "tree.h"
#include "adaptor/stack.h"
#include "ostream"

template <class T = int>
class avl : public tree<T, node_avlt<T>>
{
	// typedef:
	typedef node_avlt<T>* ptr;
	
	// auxiliar methods:
	ptr left_rotation(ptr& node);
	ptr rght_rotation(ptr& node);
	bit balnce_factor(ptr& node) const;

	ptr insert_call(ptr& parent, const T& value);
	ptr remove_call(ptr& parent, const T& value);
public:
	// constructors:
	avl(const T& value = NULL);
	~avl();

	// specific methods:
	avl<T>& operator = (const avl<T>& t);
	void insert(const T& value);
	void remove(const T& value);

	// query operations:
	ptr    search(const T& value) const;
	size_t height(ptr& parent) const;
	ptr minimum() const;
	ptr maximum() const;
	ptr predcessr(const T& value);
	ptr successor(const T& value);

	// constant methods:
	bool operator == (const avl<T>& t);

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};

//------------------------------------------------
// auxiliar methods:

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
bit avl<T>::balnce_factor(ptr& node) const
{
	return node->successor[left_child]->get_height() - node->successor[rght_child]->get_height();
}

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
}

//------------------------------------------------
// constructors:

template <class T>
avl<T>::avl(const T& value) : tree<T, node_avlt<T>>(value) {}

template <class T>
avl<T>::~avl() {}

//------------------------------------------------
// specific methods:

template <class T>
avl<T>& avl<T>::operator = (const avl<T>& t)
{

}

template <class T>
void avl<T>::insert(const T& value)
{
	insert_call(root, value);
}

template <class T>
void avl<T>::remove(const T& value)
{
	remove_call(root, value);
}

//------------------------------------------------
// query operations:

// search
template <class T>
node_avlt<T>* avl<T>::search(const T& value) const
{
	ptr it = root;
	while (it)
	{
		if (value == it->get())
			return it;
		if (value < it->get())
			it = it->successor[left_child];
		else
			it = it->successor[rght_child];
	}
}

template <class T>
size_t avl<T>::height(ptr& parent) const
{
	return parent->get_height();
}

template <class T>
node_avlt<T>* avl<T>::minimum() const
{
	ptr it = root;
	while(it->successor[left_child])
		it = it->successor[left_child];
	return it;
}

template <class T>
node_avlt<T>* avl<T>::maximum() const
{
	ptr it = root;
	while (it->successor[rght_child])
		it = it->successor[rght_child];
	return it;
}

template <class T>
node_avlt<T>* avl<T>::predcessr(const T& value)
{
	ptr it = root;
	while (it->get() > value)
	{
		if (it->successor[left_child] == nullptr)
			return nullptr;
		it = it->successor[left_child];
	}
	// it points to a value smaller than value
	
	while (it->successor[rght_child])
	{
		if (it->successor[rght_child] < value)
			it = it->successor[rght_child];
		else
		{
			if (it->successor[left_child] == nullptr)
				break;
			it = it->successor[left_child];
		}
	}
}

template <class T>
node_avlt<T>* avl<T>::successor(const T& value)
{
	ptr it = root;
	while (it->get() < value)
	{
		if (it->successor[rght_child] == nullptr)
			return nullptr;
		it = it->successor[rght_child];
	}
	// it points to a value smaller than value

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
// friend functions:

template <class T>
T* convert(const avl<T>& t)
{

}

template <class T>
std::ostream& operator << (std::ostream& out, const avl<T>& t)
{
	stack<node_avlt<T>*> nodes;

	node_avlt<T>* it = root;
	while (it)
	{
		nodes.push(it);
		it = it->successor[left_child];
	}
	
}
