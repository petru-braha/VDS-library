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
#include "stack.h"
#include "queue.h"
#include <initializer_list>

/* comments:
	- comparison functions => NODES!
	- iterator operation's order: 
		1. operator !=
		2. operator *
		3. operator ++
		- if not fixable, wrong order will throw an exception
	- sorting in liner time + linear enqueue VS O(n*lg n) constructing
	- a node can be
		- parent  - height h
		- leaf    - height 1
		- nullptr - height 0
	- does not accept repeating values
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
	avl<T>& operator = (const avl<T>& tree);
	avl<T>& clear();
	avl<T>& set_f(fct f);

	// specific methods:
	avl<T>& insert(const node_avlt<T>* const value);
	avl<T>& remove(const node_avlt<T>* const value);

	// constant methods:
	bool operator == (const avl<T>& tree) const;
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
	avl<T>& integrates(const avl<T>& tree);
	avl<T>& eliminates(const avl<T>& tree);
	avl<T>& intersects(const avl<T>& tree);

	// iterator methods:
	avl_iterator<T> begin() const;
	avl_iterator<T> end() const;

	// friend functions:
	template <class T> friend T* convert(const avl<T>& tree);
	template <class T> friend std::ostream& operator << (std::ostream& out, const avl<T>& tree);

private:
	// data members:
	node_avlt<T>* root;
	size_t n;

	// auxiliar utility:
	fct compare;
	ptr left_rotation(node_avlt<T>* const node);
	ptr rght_rotation(node_avlt<T>* const node);

	ptr insert_call(const node_avlt<T>* const value, node_avlt<T>*& parent);
	ptr remove_call(const node_avlt<T>* const value, node_avlt<T>*& parent);

public:
	static const size_t LEFT;
	static const size_t RGHT;
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
	compare = [](t x, t y)->bool { return x > y; };
}

template <class T>
avl<T>::avl(const std::initializer_list<T>& data) : avl<T>()
{
	for (auto value : data)
	{
		node_avlt<T> new_node(value);
		insert(&new_node);
	}
}

template <class T>
avl<T>::avl(const T* data, szt data_size)
{
	FOR(data_size)
	{
		ptr new_node = new node_avlt<T>(data[i]);
		insert(new_node);
	}
}

/*template <class T>
avl<T>::avl(const avl<T>& tree);

template <class T>
avl<T>::avl(const avl<T>&& tree);
*/

//------------------------------------------------
// modifier methods:

template <class T>
avl<T>& avl<T>::operator = (const avl<T>& tree)
{
	////////////////////////////////////////////////////////////
	return *this;
}

template <class T>
avl<T>& avl<T>::clear()
{
	if (empty())
		return *this;

	ptr curent = root;
	queue<ptr> nodes;
	nodes.push(curent);

	while (!nodes.empty())
	{
		curent = nodes.front();
		nodes.pop();

		if (curent->successor[LEFT])
			nodes.push(curent->successor[LEFT]);
		if (curent->successor[RGHT])
			nodes.push(curent->successor[RGHT]);

		delete curent;
	}
		
	n = 0;
	root = nullptr;
	return *this;
}

template <class T>
avl<T>& avl<T>::set_f(fct f)
{
	compare = f;
	return *this;
}

//------------------------------------------------
// specific methods:

template <class T>
avl<T>& avl<T>::insert(const node_avlt<T>* const value)
{
	if(value)
		root = insert_call(value, root);
	return *this;
}

template <class T>
avl<T>& avl<T>::remove(const node_avlt<T>* const value)
{
	if(value)
		root = remove_call(value, root);
	return *this;
}

//------------------------------------------------
// constant methods:

template <class T>
bool avl<T>::operator == (const avl<T>& tree) const
{
	if (this->n != tree.n)
		return false;
	
	avl_iterator<T> it1(this->root), it2(tree.root), dummy{};

	FOR(n)
	{
		it1 != dummy;
		it2 != dummy;
		T val1 = *it1, val2 = *it2;
		if (val1 != val2)
			return false;
		++it1;
		++it2;
	}

	return true;
}

template <class T>
size_t avl<T>::get_n() const
{
	return n;
}

template <class T>
void* avl<T>::get_f() const
{
	return (void*)compare;
}

template <class T>
bool avl<T>::empty() const
{
	return (nullptr == root && 0 == n);
}

template <class T>
void avl<T>::print() const
{
	if (empty())
		return;

	for (auto value : *this)
		std::cout << value << ' ';
	std::cout << '\n';
}

template <class T>
size_t avl<T>::get_arity() const
{
	return root->get_arity();
}

template <class T>
const node_avlt<T>* avl<T>::get_r() const
{
	return root;
}

//------------------------------------------------
// query operations:

template <class T>
size_t avl<T>::height(const node_avlt<T>* const parent) const
{
	if (nullptr == parent)
		return 0;
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
	if (empty())
		return nullptr;

	ptr it = root;
	while(it->successor[left_child])
		it = it->successor[left_child];
	return it;
}

template <class T>
const node_avlt<T>* avl<T>::maximum() const
{
	if (empty())
		return nullptr;

	ptr it = root;
	while (it->successor[rght_child])
		it = it->successor[rght_child];
	return it;
}

template <class T>
const node_avlt<T>* avl<T>::predcessr(const node_avlt<T>* value) const
{
	ptr it = root;
	while (it && compare(it->get(), value->get())) // until it points to a value smaller than value->get()
		it = it->successor[left_child];
	
	while (it && it->successor[rght_child] && compare(value->get(), it->get()))
		it = it->successor[rght_child];

	return it;
}

template <class T>
const node_avlt<T>* avl<T>::successor(const node_avlt<T>* value) const
{
	ptr it = root;
	while (it && compare(value->get(), it->get()))
		it = it->successor[rght_child];

	while (it && it->successor[left_child] && compare(it->get(), value->get()))
		it = it->successor[left_child];

	return it;
}

//------------------------------------------------
// instance synergy:

template <class T>
avl<T>& avl<T>::integrates(const avl<T>& tree)
{
	if (this->compare != tree.compare)
		hard_error("both objects impose the same comparison function");

	ptr curent = tree.root;
	queue<ptr> nodes;
	nodes.push(curent);

	while (!nodes.empty())
	{
		curent = nodes.front();
		nodes.pop();

		if (curent->successor[LEFT])
			nodes.push(curent->successor[LEFT]);
		if (curent->successor[RGHT])
			nodes.push(curent->successor[RGHT]);

		ptr copy = new node_avlt<T>(curent->get());
		insert(copy);
	}

	return *this;
}

template <class T>
avl<T>& avl<T>::eliminates(const avl<T>& tree)
{
	if (this->compare != tree.compare)
		hard_error("both objects impose the same comparison function");

	ptr curent = tree.root;
	queue<ptr> nodes;
	nodes.push(curent);

	while (!nodes.empty())
	{
		curent = nodes.front();
		nodes.pop();

		if (curent->successor[LEFT])
			nodes.push(curent->successor[LEFT]);
		if (curent->successor[RGHT])
			nodes.push(curent->successor[RGHT]);

		remove(curent);
	}

	return *this;
}

template <class T>
avl<T>& avl<T>::intersects(const avl<T>& tree) // to rethink very inneficient
{
	if (this->compare != tree.compare)
		hard_error("both objects impose the same comparison function");
	////////////////////////////////////////////////////////////////////
	return *this;
}

//------------------------------------------------
// iterator methods:

template <class T>
avl_iterator<T> avl<T>::begin() const
{
	return root;
}

template <class T>
avl_iterator<T> avl<T>::end() const
{
	return avl_iterator<T>();
}

//------------------------------------------------
// friend functions:

template <class T> 
T* convert(const avl<T>& tree)
{
	T* arr = new T[tree.n]{};
	size_t index = 0;

	for (auto value : tree)
	{
		arr[index] = value;
		index++;
	}

	return arr;
}

template <class T> 
std::ostream& operator << (std::ostream& out, const avl<T>& tree)
{
	if (tree.empty())
		return out;

	for (auto value : tree)
		out << value << ' ';
	out << '\n';
	return out;
}

//------------------------------------------------
// auxiliar utility:

template <class T>
const size_t avl<T>::LEFT = 0;

template <class T>
const size_t avl<T>::RGHT = 1;

template <class T>
node_avlt<T>* avl<T>::left_rotation(node_avlt<T>* const node)
{
	ptr it = node->successor[rght_child];
	node->successor[rght_child] = it->successor[left_child];
	it->successor[left_child] = node;

	size_t h1 = height(node->successor[left_child]);
	size_t h2 = height(node->successor[rght_child]);
	node->set_height(1 + (h1 > h2 ? h1 : h2));

	h1 = height(it->successor[left_child]);
	h2 = height(it->successor[rght_child]);
	it->set_height(1 + (h1 > h2 ? h1 : h2));
	return it;
}

template <class T>
node_avlt<T>* avl<T>::rght_rotation(node_avlt<T>* const node)
{
	ptr it = node->successor[left_child];
	node->successor[left_child] = it->successor[rght_child];
	it->successor[rght_child] = node;
	
	size_t h1 = height(node->successor[left_child]);
	size_t h2 = height(node->successor[rght_child]);
	node->set_height(1 + (h1 > h2 ? h1 : h2));

	h1 = height(it->successor[left_child]);
	h2 = height(it->successor[rght_child]);
	it->set_height(1 + (h1 > h2 ? h1 : h2));
	return it;
}

//------------------------------------------------
// auxiliar utility x 2:

template <class T>
node_avlt<T>* avl<T>::insert_call(const node_avlt<T>* const value, node_avlt<T>*& parent)
{
	// base case
	if (nullptr == parent)
	{
		n++;
		return new node_avlt<T>(value->get());
	}

	if (value->get() == parent->get())
		return parent;
	
	// recursive calls
	if (compare(parent->get(), value->get()))
		parent->successor[LEFT] = insert_call(value, parent->successor[LEFT]);
	else
		parent->successor[RGHT] = insert_call(value, parent->successor[RGHT]);

	// height
	size_t h1 = height(parent->successor[LEFT]);
	size_t h2 = height(parent->successor[RGHT]);
	parent->set_height(1 + (h1 > h2 ? h1 : h2));

	// rebalancing
	int balance_factor = parent->balance_factor();

	if (balance_factor > 1 && compare(parent->successor[LEFT]->get(), value->get()))
		return rght_rotation(parent);
	if (balance_factor < -1 && compare(value->get(), parent->successor[RGHT]->get()))
		return left_rotation(parent);

	if (balance_factor > 1 && compare(value->get(), parent->successor[LEFT]->get()))
	{
		parent->successor[LEFT] = left_rotation(parent->successor[LEFT]);
		return rght_rotation(parent);
	}

	if (balance_factor < -1 && compare(parent->successor[RGHT]->get(), value->get()))
	{
		parent->successor[RGHT] = rght_rotation(parent->successor[RGHT]);
		return left_rotation(parent);
	}

	return parent;
}

template <class T>
node_avlt<T>* avl<T>::remove_call(const node_avlt<T>* const value, node_avlt<T>*& parent)
{
	// base case
	if (nullptr == parent)
		return parent;

	// searching for the value
	if (compare(parent->get(), value->get()))
		parent->successor[LEFT] = remove_call(value, parent->successor[LEFT]);
	else if (compare(value->get(), parent->get()))
		parent->successor[RGHT] = remove_call(value, parent->successor[RGHT]);
	
	else // found the value
	{
		if (parent->successor[LEFT])
		{
			if (parent->successor[RGHT]) // both
			{
				auto to_remove = successor(parent);
				std::cout << "DADA " << to_remove->get() << " DADAD";
				parent->successor[RGHT] = 
					remove_call(to_remove, parent->successor[RGHT]);
			}
			else // only left
			{
				n--;
				auto it = parent;
				parent = parent->successor[LEFT];
				delete it;
			}
		}

		else
		{
			if (parent->successor[RGHT]) // only right
			{
				n--;
				auto it = parent;
				parent = parent->successor[RGHT];
				delete it;
			}
			else // no children
			{
				n--;
				delete parent;
				parent = nullptr;
			}
		}
	}

	if (nullptr == parent)
		return nullptr;

	// height
	size_t h1 = height(parent->successor[LEFT]);
	size_t h2 = height(parent->successor[RGHT]);
	parent->set_height(1 + (h1 > h2 ? h1 : h2));

	// rebalancing
	int balance_factor = parent->balance_factor();
	ptr left = parent->successor[LEFT];
	ptr rght = parent->successor[RGHT];

	if (balance_factor > 1 && left->balance_factor() >= 0)
		return rght_rotation(parent);
	if (balance_factor < -1 && rght->balance_factor() <= 0)
		return left_rotation(parent);

	if (balance_factor > 1 && left->balance_factor() < 0)
	{
		parent->successor[left_child] = left_rotation(parent->successor[left_child]);
		return rght_rotation(parent);
	}

	if (balance_factor < -1 && rght->balance_factor() > 0)
	{
		parent->successor[rght_child] = rght_rotation(parent->successor[rght_child]);
		return left_rotation(parent);
	}

	return parent;
}
