#pragma once

template <class T>
class adaptor
{
public:
	// specific methods:
	virtual void push(const T& value) = 0;
	virtual void pop() = 0;

	// constant methods:
	virtual size_t getn() const = 0;
	virtual bool  empty() const = 0;
};
