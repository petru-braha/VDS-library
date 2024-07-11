#pragma once
#include "pch.h"
#include "stack.h"

//------------------------------------------------
// constructors:

template <class T>
stack<T>::stack() : adaptor() {};

template <class T>
stack<T>::stack(std::initializer_list<T>& val) : adaptor(val) {};

template <class T>
stack<T>::stack(T* val, const size_t& val_size) : adaptor(val, val_size) {};

template <class T>
stack<T>::stack(const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
stack<T>::stack(const adaptor<T>&& adp)
{
	this->values = adp.values;
	delete adp;
}

//------------------------------------------------
// specific methods:

template <class T>
stack<T>& stack<T>::operator = (const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
T stack<T>::top() const
{
	return this->values[0];
}

template <class T>
void stack<T>::push(const T& val)
{
	values.insert(val, 0);
}

template <class T>
void stack<T>::pop()
{
	values.remove(0);
}

//------------------------------------------------
// constant methods:

template <class T>
bool stack<T>::operator == (const adaptor<T>& adp) const
{
	return this->values == adp.values;
}

template <class T>
void stack<T>::prnt() const
{
	std::cout << '\n' << "top->bottom: ";
	for (auto i : values)
		std::cout << i << ' ';
	std::cout << '\n';
}
