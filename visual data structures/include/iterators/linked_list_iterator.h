#pragma once
#include "basic_iterator.h"
#include "node/node_list.h"

template <class T>
class linked_list_iterator : public basic_iterator<T, linked_list_iterator<T>>
{
	// data members:
	node_list<T>* value;

public:
	// constructors:
	linked_list_iterator(node_list<T>*& value);

	// specific methods:
	T    operator  * () const;
	void operator ++ ();
	bool operator != (const linked_list_iterator<T>& it) const;
};

//------------------------------------------------
// constructors:

template <class T>
linked_list_iterator<T>::linked_list_iterator(node_list<T>*& value) : value(value) {}

//------------------------------------------------
// specific methods:

template <class T>
T linked_list_iterator<T>::operator *() const
{
	return *value;
}

template <class T>
void linked_list_iterator<T>::operator ++()
{
	value = value->successor[0];
}

template <class T>
bool linked_list_iterator<T>::operator != (const linked_list_iterator<T>& it) const
{
	return value != it.value;
}
