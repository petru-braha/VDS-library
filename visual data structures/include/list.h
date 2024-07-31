#pragma once
#include "bureaucracy.h"
#include "node/node_list.h"
#define head_node nullptr // to precisely manipulate the first node of the list


template <class T>
class list 
{
	// typedefs:
	typedef node_list<T>* ptr;
	typedef const size_t& szt;
	typedef const T& type;
protected:
	// data members:
	node_list<T>* frst, * last;
	size_t n;

	// constructors:
	virtual ~list();
	list();
	list(const list<T>& l) = default;
	list(const list<T>&& l) = default;
public:
	// modifier methods:
	void clear();
	
	// specific methods:
	void atypical_insert(type value, szt index);
	void atypical_remove(szt index);

	// traditional ways:
	void insert(ptr& value, ptr& before_inserted);
	void remove(ptr& before_removed);

	// constant methods:
	size_t getn() const;
	bool  empty() const;
	ptr get_frst() const;
	ptr get_last() const;


private: // linked_list inherit this class
	// friend functions:
	friend class adaptor;
};

// comments:
// it is not allowed for adaptors to interact with private data of a linked_list => private friendship
// for insert and remove methods, the case frst actually means the second node
// PAY ATTENTION TO THE SYNTAX: "BEFORE_INSERTED", "BEFORE_REMOVED"
// allows repeating values

//------------------------------------------------
// constructors:

template <class T>
list<T>::~list()
{
	clear();
}

template <class T>
list<T>::list()
{
	frst = last = nullptr;
	n = 0;
}

//------------------------------------------------
// modifier methods:

template <class T>
void list<T>::clear()
{
	ptr it = frst;
	while (it)
	{
		it = it->successor[0];
		delete frst;
		frst = it;
		n--;
	}
	frst = last = nullptr;
}

//------------------------------------------------
// specific methods:
 
template <class T>
void list<T>::atypical_insert(type value, szt index)
{
	// optimisation:
	if (index == n)
	{
		last->successor[0] = new node_list<T>(value);
		last = last->successor[0];
		n++;
		return;
	}

	if (index == 0)
	{
		node_list<T>* it = new node_list<T>(value);
		it->successor[0] = frst;
		frst = it;
		n++;
		return;
	}

	node_list<T>* it = frst;
	for (size_t i = 0; i + 1 < index; i++)
		it = it->successor[0];
	if (it == nullptr)
		hard_error("bad index");

	node_list<T>* nxt = it->successor[0];
	it->successor[0] = new node_list<T>(value);
	it = it->successor[0];
	it->successor[0] = nxt;
	n++;
}

template <class T>
void list<T>::atypical_remove(szt index)
{
	if (index >= n || index < 0)
	{
		eazy_error("bad index");
		return;
	}

	// deleting the first element
	if (index == 0)
	{
		node_list<T>* it = frst;
		frst = frst->successor[0];
		delete it;
		n--;
		return;
	}

	node_list<T>* it = frst;
	for (size_t i = 0; i + 1 < index; i++)
		it = it->successor[0];
	node_list<T>* nxt = it->successor[0];
	it->successor[0] = nxt->successor[0];
	delete nxt;
	n--;
}

template <class T>
void list<T>::insert(ptr& value, ptr& before_inserted) 
{
	n++;
	ptr actual = new ptr(value->get()); // if value has successors

	// case head_node
	if (before_inserted == head_node)
	{
		if (empty())
		{
			frst = last = actual;
			return;
		}
		
		actual->successor[0] = frst; // not empty => insert as a first node
		frst = actual;
		return;
	}

	// case frst
	if (before_inserted == frst)
	{
		actual->successor[0] = frst->successor[0];
		frst->successor[0] = actual;
		return;
	}

	// case last
	if (before_inserted == last)
	{
		last = last->successor[0] = actual;
		return;
	}

	// case mid
	actual->successor[0] = before_inserted->successor[0];
	before_inserted->successor[0] = actual;
}

template <class T>
void list<T>::remove(ptr& before_removed)
{
	if (empty())
		fatal_error("no more memory");
	n--;

	// case head_node
	if (before_removed == head_node)
	{
		ptr it = frst;
		frst = frst->successor[0];
		delete it;
		return;
	}

	// case mid, similiar to case frst, there is no case last
	ptr it = before_removed->successor[0];
	before_removed->successor[0] = it->successor[0];
	delete it;
	return;
}

//------------------------------------------------
// constant methods:

template <class T>
size_t list<T>::getn() const
{
	return n;
}

template <class T>
bool list<T>::empty() const
{
	return n == 0;
}

template <class T>
node_list<T>* list<T>::get_frst() const
{
	return frst;
}

template <class T>
node_list<T>* list<T>::get_last() const
{
	return last;
}

