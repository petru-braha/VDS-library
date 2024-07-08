#pragma once

template <class T = int>
class node
{
public:
	virtual void set(const T& data) = 0;
	virtual T    get() const = 0;
	virtual ~node(){}
};
