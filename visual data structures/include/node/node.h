#pragma once

typedef unsigned char bit;
typedef unsigned long long int ull;

template <class T = int>
class node
{
	T data;
public:
	node(const T& val = NULL) : data(val) {}
	virtual ~node() = 0;

	T& get() const { return data; }
};

template <class T>
node<T>::~node() {}
