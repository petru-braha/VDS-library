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
	stack(const stack<T>& s) = default;
	//stack(const stack<T>&& s) = default;
	~stack() = default;

	// specific methods
	stack<T>& operator = (const stack<T>& s);
	T    top() const;
	void push(const T& val);
	void pop();

	// constant methods
	bool operator == (const stack<T>& s) const;
	void prnt() const;
};