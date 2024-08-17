#pragma once
#include "bureaucracy.h"
#include "tree.h"
#include "bst.h"
#include <ostream>

template <class T = int>
class avl : public tree<T, node_avlt<T>>, bst<T, node_avlt<T>>
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const size_t& szt;
	
	typedef node_avlt<T>* ptr;
	typedef const node_avlt<T>*& ptr_ref;
	typedef const node_avlt<T>* ptr_return;

	// iterator concept:
	class iterator
	{
		ptr current;
		//stack<ptr> nodes;
	public:
		iterator(ptr node);

		T    operator *  () const;
		void operator ++ ();
		bool operator != (const iterator& s) const;
	};

	// auxiliar utility:
	ptr left_rotation(ptr& node);
	ptr rght_rotation(ptr& node);
	bit balnce_factor(const ptr& node) const;
public:
	// constructors:
	~avl();
	avl();
	avl(const std::initializer_list<T>& val);
	avl(const T* val, szt val_size);
	avl(const avl<T>& t);
	avl(const avl<T>&& t);

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// modifier methods:
	avl<T>& operator = (const avl<T>& t);
	void clear();
	void setf(fct f);

	// specific methods:
	void insert(const ptr& value);
	void remove(const ptr& value);

	// query operations:
	size_t height(ptr_ref parent) const;
	ptr_return search(const T& value) const;
	ptr_return minimum() const;
	ptr_return maximum() const;
	ptr_return predcessr(ptr_ref value) const;
	ptr_return successor(ptr_ref value) const;

	// constant methods:
	bool operator == (const avl<T>& t);
	size_t get_arity() const;
	size_t		getn() const;
	ptr_return	getr() const;
	void*		getf() const;
	void		prnt() const;
	bool	   empty() const;

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};

// comments:
// warning: test the iterator class

//------------------------------------------------
// auxiliar utility:

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
}
*/

//------------------------------------------------
// constructors:
/*
template <class T>
avl<T>::~avl() {}

template <class T>
avl<T>::avl() : tree<T, node_avlt<T>>() {}

//------------------------------------------------
// iterator methods:

template <class T>
avl<T>::iterator::iterator(ptr node) : nodes()
{
	ptr it = node;
	this->current = it;
	nodes.push(it);
}

template <class T>
T avl<T>::iterator::operator * () const
{
	while (current)
	{
		nodes.push(current);
		current = current->successor[left_child];
	}

	current = nodes.top();
	nodes.pop();
	return current->get();
}

template <class T>
void avl<T>::iterator::operator ++ ()
{
	current = current->successor[rght_child];
}

template <class T>
bool avl<T>::iterator::operator != (const iterator& s) const
{
	return !nodes.empty() || current;
}

template <class T>
typename avl<T>::iterator avl<T>::begin() const
{
	return iterator(this->root);
}

template <class T>
typename avl<T>::iterator avl<T>::end() const
{
	return iterator(nullptr);
}

//------------------------------------------------
// specific methods:

//template <class T>
//avl<T>& avl<T>::operator = (const avl<T>& t);

template <class T>
void avl<T>::insert(const ptr& value)
{
	//insert_call(root, value);
}

template <class T>
void avl<T>::remove(const ptr& value)
{
	//remove_call(root, value);
}

//------------------------------------------------
// query operations:

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
/*
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
}*/

//------------------------------------------------
// friend functions:
