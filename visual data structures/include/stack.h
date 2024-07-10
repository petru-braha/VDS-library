#pragma once
#include "adaptor.h"

template <class T>
class stack : public adaptor<T>
{
public:
	// constructors
	stack();
	stack(std::initializer_list<T>& val);
	stack(T* val);
	//stack(const adaptor<T>& s) = default;
	//stack(const adaptor<T>&& s) = default;
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