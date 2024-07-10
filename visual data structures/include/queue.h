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
	//queue(const adaptor<T>& adp) = default;
	//queue(const adaptor<T>&& adp) = default;
	~queue() = default;

	// specific methods:
	queue<T>& operator = (const adaptor<T>& adp);
	T	 front() const;
	T	 back() const;
	void push(const T& val);
	void pop();

	// constant methods:
	bool operator == (const adaptor<T>& adp) const;
	void prnt() const;
};
