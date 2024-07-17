#pragma once
#include "bureaucracy.h"
#include "node/node_list.h"
#include <initializer_list>
#include <ostream>

template <class T = int>
class linked_list
{
	// typedef
	typedef const T& type;
	typedef bool (*fct)(type, type);

	// data members:
	node_list<T>* frst, * last;
	size_t n;

	// iterator concept:
	class iterator
	{
		node_list<T>* value;

	public:
		iterator(node_list<T>* val);

		T    operator  * () const;
		void operator ++ ();
		bool operator != (const iterator& two) const;
	};

	// auxiliar utility:
	//fct compare();
public:
	// constructors:
	~linked_list();
	linked_list(const T& val = NULL);
	linked_list(const std::initializer_list<T>& val);
	linked_list(T* val, const size_t& val_size);
	linked_list(const linked_list<T>& l);
	linked_list(const linked_list<T>&& l);

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// specific methods:
	linked_list<T>& operator = (const linked_list<T>& l);
	void insert(const T& value, const size_t& index = n);
	void remove(const T& index); // to enchance the use of the stack and queue
	bool search(const T& value) const;

	// constant methods:
	bool operator == (const linked_list<T>& l) const;
	T& operator[](const size_t& index) const;
	size_t getn() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions:
	friend T* convert(const linked_list<T>& l);
	friend std::ostream& operator << (std::ostream& out, const linked_list<T>& l);
	friend void* collection_ptr(const linked_list<T>& l); // just for the collection!
};

// comments:
// if linked_lists would be sortable, merge_sort and quick_sort Lomuto scheme are the obvious choice

//------------------------------------------------
// constructors:

template <class T>
linked_list<T>::~linked_list()
{
	node_list<T>* it = frst;
	while (it)
	{
		it = it->successor[0];
		delete frst;
		frst = it;
	}
}

template <class T>
linked_list<T>::linked_list(const T& val)
{
	this->frst = this->last = new node_list<T>(val);
	this->n = 1;
}

template <class T>
linked_list<T>::linked_list(const std::initializer_list<T>& val)
{
	this->frst = new node_list<T>(*(val.begin()));

	node_list<T>* it = frst;
	for (auto i = (val.begin() + 1); i < (val.end()); i++)
	{
		it->successor[0] = new node_list<T>(*i);
		it = it->successor[0];
	}

	this->last = it;
	this->n = val.size();
}

template <class T>
linked_list<T>::linked_list(T* val, const size_t& val_size)
{
	this->frst = new node_list<T>(*val);
	val++;
	node_list<T>* it = frst;

	size_t i = 1;
	while (i < val_size)
	{
		it->successor[0] = new node_list<T>(*val);
		it = it->successor[0];
		val++;
		i++;
	}

	this->last = it;
	this->n = i;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& l)
{
	this->frst = new node_list<T>(*l.begin());

	node_list<T>* it = frst;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->last = it;
	this->n = l.getn();
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>&& l)
{
	this->frst = new node_list<T>(*l.begin());

	node_list<T>* it = frst;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->last = it;
	this->n = l.getn();
	delete l;
}

//------------------------------------------------
// iterator methods:

template <class T>
linked_list<T>::iterator::iterator(node_list<T>* val) : value(val) {};

template <class T>
T linked_list<T>::iterator::operator  * () const
{
	return value->get();
}

template <class T>
void linked_list<T>::iterator::operator ++ ()
{
	value = value->successor[0];
}

template <class T>
bool linked_list<T>::iterator::operator != (const iterator& two) const
{
	return value != two.value;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::begin() const
{
	return iterator(frst);
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::end() const
{
	return iterator(last->successor[0]);
}

//------------------------------------------------
// specific methods:

template <class T>
linked_list<T>& linked_list<T>::operator = (const linked_list<T>& l)
{
	delete this;
	this->frst = new node_list<T>(*l.begin());

	node_list<T>* it = frst;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->last = it;
	this->n = l.getn();
}

template <class T>
void linked_list<T>::insert(const T& value, const size_t& index)
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
void linked_list<T>::remove(const T& index)
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
bool linked_list<T>::search(const T& value) const
{
	for (auto i : *this)
		if (i == value)
			return true;
	return false;
}

//------------------------------------------------
// constant methods:

template <class T>
bool linked_list<T>::operator == (const linked_list<T>& l) const
{
	if (this->n != l.n)
		return false;
	node_list<T>* it = frst;
	for (auto i : l)
	{
		if (it->get() != i)
			return false;
		it = it->successor[0];
	}

	return true;
}

template <class T>
T& linked_list<T>::operator [] (const size_t& index) const
{
	// base case:
	if (index >= n)
		hard_error("bad index");

	// optimisation:
	if (index == n - 1)
		return last->get();

	node_list<T>* it = this->frst;
	for (size_t i = 0; i < index; i++)
		it = it->successor[0];
	return it->get();
}

template <class T>
size_t linked_list<T>::getn() const
{
	return n;
}

template <class T>
void   linked_list<T>::prnt() const
{
	for (auto i : *this)
		std::cout << i << ' ';
}

template <class T>
bool linked_list<T>::empty() const
{
	return n == 0;
}

//------------------------------------------------
// friend functions:

template <class T>
T* convert(const linked_list<T>& l)
{
	T* ptr = new T[n];
	size_t index = 0;
	for (auto i : l)
		ptr[index++] = i;
	return ptr;
}

template <class T>
std::ostream& operator << (std::ostream& out, const linked_list<T>& l)
{
	node_list<T>* it = l.frst;
	while (it)
	{
		out << it->get() << ' ';
		it = it->successor[0];
	}

	return out;
}

template <class T>
void* collection_ptr(const linked_list<T>& l)
{
	return (void*)frst;
}