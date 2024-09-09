#pragma once

template <class T>
class adaptor
{
public:
	// specific methods:
	virtual adaptor<T>& push(const T& value) = 0;
	virtual adaptor<T>& pop() = 0;

	// constant methods:
	virtual size_t get_n() const = 0;
	virtual bool   empty() const = 0;
};
