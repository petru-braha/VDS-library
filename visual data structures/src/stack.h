#pragma once
#include "list.h"
#include "adaptor.h"

template <class T = int>
class stack : public adaptor<T>
{
	// data members:
	list<T> values;
public:
	// constructors:
	~stack() = default;
	stack();
	stack(std::initializer_list<T>& val);
	stack(T* val, const size_t& val_size);
	stack(const adaptor<T>& adp);
	stack(const adaptor<T>&& adp);

	// modifier methods:
	stack<T>& operator = (const adaptor<T>& adp);
	
	// specific methods:
	T    top() const;
	void push(const T& val);
	void pop();

	// constant methods:
	bool operator == (const adaptor<T>& adp) const;
	size_t getn() const;
	bool  empty() const;
};

//------------------------------------------------
// constructors:

template <class T>
stack<T>::stack() : values() {};

template <class T>
stack<T>::stack(std::initializer_list<T>& val) : values() 
{
	for (auto key : val)
		push(key);
}

template <class T>
stack<T>::stack(T* val, const size_t& val_size) : values()
{
	FOR(val_size)
	{
		push(*val);
		val++;
	}
}

template <class T>
stack<T>::stack(const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
stack<T>::stack(const adaptor<T>&& adp)
{
	this->values = adp.values;
}

//------------------------------------------------
// modifier methods:

template <class T>
stack<T>& stack<T>::operator = (const adaptor<T>& adp)
{
	this->values = adp.values;
}

//------------------------------------------------
// specific methods:

template <class T>
T stack<T>::top() const
{
	if(!empty())
		return values.frst;
	hard_error("no data");
}

template <class T>
void stack<T>::push(const T& val)
{
	values.atypical_insert(val, 0);
}

template <class T>
void stack<T>::pop()
{
	if(!empty())
		values.atypical_remove(0);
	hard_error("no data");
}

//------------------------------------------------
// constant methods:

template <class T>
bool stack<T>::operator == (const adaptor<T>& adp) const
{
	return this->values == adp.values;
}

template <class T>
size_t stack<T>::getn() const
{
	return values.n;
}

template <class T>
bool stack<T>::empty() const
{
	return values.empty();
}
