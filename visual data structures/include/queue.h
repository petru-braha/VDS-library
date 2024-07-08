#pragma once
#include "adaptor.h"

template <class T>
class queue : public adaptor<T>
{
public:
	// constructors:
	queue();
	queue(std::initializer_list<T>& val);
	queue(T* val);
	queue(const queue<T>& q) = default;
	//queue(const queue<T>&& q) = default;
	~queue() = default;

	// specific methods:
	queue<T>& operator = (const queue<T>& q);
	T	 front() const;
	T	 back() const;
	void push(const T& val);
	void pop();

	// constant methods:
	bool operator == (const queue<T>& q) const;
	void prnt() const;
};
