#pragma once
#include "bureaucracy.h"

#include "node/node_double_list.h"

/* comments:
	- simplified version of a double linked list;
	- its purpose is to support adaptors and hash_table
	- to serve the developer and not the user
*/

template <class T = int>
class double_linked_list
{
	structure_typedefs;
	typedef node_double_list<T>* ptr;
	typedef const node_double_list<T>* ptr_return;

public:
	// constructors:
	~double_linked_list();
	double_linked_list();

	// modifier methods:
	double_linked_list<T>& clear();
	double_linked_list<T>& set_f(fct f);

	// specific methods:
	double_linked_list<T>& insert(const node_double_list<T>* const value, node_double_list<T>* const before_inserted = head_node);
	double_linked_list<T>& remove(node_double_list<T>*& node);

	// constant methods:
	bool   empty() const;
	void   print() const;

	ptr_return get_node(szt index) const;
	ptr_return get_head() const;
	ptr_return get_tail() const;

private:
	// data members:
	node_double_list<T>* head;
	node_double_list<T>* tail;

	// auxiliar utility:
	fct compare;

public:
	static node_double_list<T>* const head_node;
};

//------------------------------------------------
// constructors:

template <class T>
double_linked_list<T>::~double_linked_list()
{
	clear();
}

template <class T>
double_linked_list<T>::double_linked_list()
{
	head = tail = nullptr;
	compare = [](t x, t y)->bool { return x > y; };
}

//------------------------------------------------
// modifier methods:

template <class T>
double_linked_list<T>& double_linked_list<T>::clear()
{
	ptr it = head;
	while (it)
	{
		head = it->successor[0];
		delete it;
		it = head;
	}

	head = tail = nullptr;
	return *this;
}

template <class T>
double_linked_list<T>& double_linked_list<T>::set_f(fct f)
{
	compare = f;
}

//------------------------------------------------
// specific methods:

template <class T>
double_linked_list<T>& double_linked_list<T>::insert(const node_double_list<T>* const value, node_double_list<T>* const before_inserted)
{
	ptr new_node = new node_double_list<T>(value->get());
	if (head_node == before_inserted)
	{
		new_node->successor[0] = head;
		head->predecessor[0] = new_node;
		head = new_node;
		return *this;
	}

	new_node->successor[0] = before_inserted->successor[0];
	before_inserted->successor[0] = new_node;
	new_node->predecessor[0] = before_inserted;

	if (nullptr == new_node->successor[0])
		tail = new_node;
	
	return *this;
}

template <class T>
double_linked_list<T>& double_linked_list<T>::remove(node_double_list<T>*& node)
{
	if (node->predecessor[0])
		node->predecessor[0]->successor[0] = node->successor[0];
	else
		head = node->successor[0];

	if (node->successor[0])
		node->successor[0]->predecessor[0] = node->predecessor[0];
	else
		tail = node->predecessor[0];
	
	delete node;
	return *this;
}

//------------------------------------------------
// constant methods:

template <class T>
bool double_linked_list<T>::empty() const
{
	return (nullptr == head && nullptr == tail);
}

template <class T>
void double_linked_list<T>::print() const
{
	if (empty())
		return;

	for (ptr it = head; it; it = it->successor[0])
		std::cout << it->get() << ' ';
	std::cout << '\n';
}

template <class T>
const node_double_list<T>* double_linked_list<T>::get_node(szt index) const
{
	ptr it = head;
	FOR(index)
		it = it->successor[0];

	return it;
}

template <class T>
const node_double_list<T>* double_linked_list<T>::get_head() const
{
	return head;
}

template <class T>
const node_double_list<T>* double_linked_list<T>::get_tail() const
{
	return tail;
}

//------------------------------------------------
// auxiliar utility:

template <class T>
node_double_list<T>* const double_linked_list<T>::head_node = nullptr;
