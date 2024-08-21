#pragma once
#include "basic_iterator.h"

template <class T>
class array_iterator : public basic_iterator<T>
{
	// data members:
	T* value;

public:
	// constructors:
	array_iterator(T& value);

	// specific methods:
	T		operator  * () const;
	void	operator ++ ();
	bool	operator != (const array_iterator<T>& it) const;
};

//------------------------------------------------
// constructors:

template <class T>
array_iterator<T>::array_iterator(T& value) : value(&value) {}

//------------------------------------------------
// specific methods:

template <class T>
T array_iterator<T>::operator*() const
{
	return *value;
}

template <class T>
void array_iterator<T>::operator++()
{
	value++;
}

template <class T>
bool array_iterator<T>::operator!=(const array_iterator<T>& it) const
{
	return value != it.value;
}
