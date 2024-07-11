#pragma once
#include "adaptor.h"

template <class T>
class stack : public adaptor<T>
{
public:
	// constructors
	stack();
	stack(std::initializer_list<T>& val);
	stack(T* val, const size_t& val_size);
	stack(const adaptor<T>& adp);
	stack(const adaptor<T>&& adp);
	~stack() = default;

	// specific methods
	stack<T>& operator = (const adaptor<T>& adp);
	T    top() const;
	void push(const T& val);
	void pop();

	// constant methods
	bool operator == (const adaptor<T>& adp) const;
	void prnt() const;
};