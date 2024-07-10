#pragma once

template <class T = int>
class node
{
	T data;
public:
	node(const T& val = NULL) : data(val) {}
	virtual ~node() = 0;

	void set(const T& data) { this->data = data; }
	T    get() const { return data; }
};

template <class T>
node<T>::~node() {}
