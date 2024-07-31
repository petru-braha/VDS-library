#pragma once
#include "list.h"
#include <initializer_list>
#include <ostream>

template <class T = int>
class linked_list : public list<T>
{
	// typedef:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef node_list<T>* ptr;
	typedef const linked_list<T>& lnkl;

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
	fct compare = [](type x, type y)->bool { return x > y; };
public:
	// constructors:
	~linked_list();
	linked_list();
	linked_list(const std::initializer_list<T>& val);
	linked_list(const T* val, const size_t& val_size);
	linked_list(const linked_list<T>& l);
	linked_list(const linked_list<T>&& l);

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// modifier methods:
	linked_list<T>& operator = (const linked_list<T>& l);
	void setf(fct f);

	// specific methods:
	void sort();

	// query operations:
	ptr search(const T& value) const;
	ptr mimimum() const;
	ptr maximum() const;
	ptr predcessr(const T& value) const;
	ptr successor(const T& value) const;

	// constant methods:
	bool  operator == (const linked_list<T>& l) const;
	void* getf() const;
	void  prnt() const;
	bool empty() const = default;

	// friend functions:
	friend T* convert(const linked_list<T>& l);

	friend linked_list<T> linking(const linked_list<T>& one, const linked_list<T>& two);
	friend linked_list<T> ejectin(const linked_list<T>& one, const linked_list<T>& two);
	friend linked_list<T> crossng(const linked_list<T>& one, const linked_list<T>& two);

	friend std::ostream& operator << (std::ostream& out, const linked_list<T>& l);
	friend void* collection_ptr(const linked_list<T>& l); // just for the collection!
};

// comments:
// how to sort: merge_sort and quick_sort_Lomuto_scheme
// allows repeating values

//------------------------------------------------
// constructors:

template <class T>
linked_list<T>::~linked_list()
{
	clear();
}

template <class T>
linked_list<T>::linked_list() : list<T>() {}

template <class T>
linked_list<T>::linked_list(const std::initializer_list<T>& val) : list<T>()
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
linked_list<T>::linked_list(const T* val, const size_t& val_size) : list<T>()
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
linked_list<T>::linked_list(const linked_list<T>& l) : list<T>()
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
linked_list<T>::linked_list(const linked_list<T>&& l) : list<T>()
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
T linked_list<T>::iterator::operator * () const
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
	return iterator(last->successor[0]); // nullptr
}

//------------------------------------------------
// modifier methods:

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
void linked_list<T>::setf(fct f)
{
	this->compare = f;
}

//------------------------------------------------
// specific methods:

//template <class T>
//void linked_list<T>::sort();

//------------------------------------------------
// query operations:

template <class T>
node_list<T>* linked_list<T>::search(const T& value) const
{
	for (auto i : *this)
		if (i == value)
			return true;
	return false;
}

template <class T>
node_list<T>* linked_list<T>::mimimum() const
{
	ptr it = frst;
	for(auto i : *this)
		if()
}

template <class T>
node_list<T>* linked_list<T>::maximum() const
{

}

template <class T>
node_list<T>* linked_list<T>::predcessr(const T& value) const
{

}

template <class T>
node_list<T>* linked_list<T>::successor(const T& value) const
{

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
void* linked_list<T>::getf() const
{
	return this->compare;
}

template <class T>
void linked_list<T>::prnt() const
{
	ptr it = frst;
	for (; it; it = it->successor[0])
		std::cout << it->get() << ' ';
	std::cout << '\n';
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