#pragma once
#include <initializer_list>
#include "linked_list.h"

template <class T = int>
class adaptor
{
protected:
	linked_list<T> values;
public:
	//constructors:
	adaptor() : values() {};
	adaptor(std::initializer_list<T>& val) : values(val) {};
	adaptor(T* val) : values(val) {};
	adaptor(const adaptor<T>& adp) = default;
	//adaptor(const adaptor<T>&& adp) = default;
	virtual ~adaptor() = default;

	// specific methods:
	virtual void push(const T& val) = 0;
	virtual void pop() = 0;

	// constant methods:
	size_t get_size() const { return values.getn(); }
	bool  empty() const { return values.empty(); }
};
