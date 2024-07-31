#pragma once

template <class T>
class adaptor
{
public:
	virtual ~adaptor() = default;

	// specific methods:
	virtual void push(const T& val) = 0;
	virtual void pop() = 0;

	// constant methods:
	size_t getn() const = 0;
	bool  empty() const = 0;
};

// comments:
// has limited functionality compared to a linked list
// allows repeating values
