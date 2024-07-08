#pragma once
#include "pch.h"
#include "queue.h"

//------------------------------------------------
// constructors:

template <class T>
queue<T>::queue() : adaptor() {};

template <class T>
queue<T>::queue(std::initializer_list<T>& val) : adaptor(val) {};

template <class T>
queue<T>::queue(T* val) : adaptor(val) {};

//------------------------------------------------
// specific methods:

template <class T>
T queue<T>::front() const
{
	return values[0];
}

template <class T>
T queue<T>::back() const
{
	return values[values.getn() - 1];
}

template <class T>
void queue<T>::push(const T& val)
{
	values.insert(val);
}

template <class T>
void queue<T>::pop()
{
	values.remove[0];
}

//------------------------------------------------
// constant methods:

template <class T>
void queue<T>::prnt() const
{
	std::cout << '\n' << "front->back: ";
	for (auto i : values)
		std::cout << i << ' ';
	std::cout << '\n';
}
