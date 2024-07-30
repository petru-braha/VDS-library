#pragma once
#include "node/node_list.h"
#include <initializer_list>

template <class T>
class adaptor
{
protected:
	// data members:
	node_list<T>* frst, * last;
	size_t n;
public:
	//constructors:
	virtual ~adaptor() = default;
	adaptor();
	adaptor(std::initializer_list<T>& val);
	adaptor(T* val, const size_t& val_size);

	// specific methods:
	virtual void push(const T& val) = 0;
	virtual void pop() = 0;

	// constant methods:
	size_t getn() const;
	bool  empty() const;

	// friend functions:
	friend T* convert(const adaptor<T>& adp);
	friend std::ostream& operator << (std::ostream& out, const adaptor<T>& adp);
};

// comments:
// it is similar to a linked list, but has limited functionality
// allows repeating values

