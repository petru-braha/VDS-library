#pragma once

template <class T>
class node
{
	// data members:
	T data;
public:
	// constructors:
	node(const T& value = NULL);
	virtual ~node() = 0;

	// specific methods:
	T& get() const;
};

template <class T>
node<T>::~node() {}
