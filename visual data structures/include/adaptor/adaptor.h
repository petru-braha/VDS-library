#pragma once
#include "linked_list.h"
#include <initializer_list>

template <class T = int>
class adaptor
{
protected:
	linked_list<T> values;
public:
	//constructors:
	adaptor() : values() {};
	adaptor(std::initializer_list<T>& val) : values(val) {};
	adaptor(T* val, const size_t& val_size) : values(val, val_size) {};
	virtual ~adaptor() = default;

	// specific methods:
	virtual void push(const T& val) = 0;
	virtual void pop() = 0;

	// constant methods:
	size_t get_size() const { return values.getn(); }
	bool  empty() const { return values.empty(); }

	// friend functions:
	friend T* convert(const adaptor<T>& adp) { return convert(adp.values); }
	friend std::ostream& operator << (std::ostream& out, const adaptor<T>& adp) { out << adp.values; return out; }
};
