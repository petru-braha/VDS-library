#pragma once
#include "linked_list.h"
#include "adaptor.h"

template <class T = int>
class stack : public adaptor<T>
{
	// data members:
	linked_list<T> values;
public:
	// constructors:
	~stack() = default;
	stack();
	stack(std::initializer_list<T>& val);
	stack(const T* val, const size_t& val_size);
	stack(const stack<T>& s);
	stack(const stack<T>&& s);

	// modifier methods:
	stack<T>& operator = (const stack<T>& s);
	
	// specific methods:
	T    top() const;
	void push(const T& value);
	void pop();

	// constant methods:
	bool operator == (const stack<T>& s) const;
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
stack<T>::stack(const T* val, const size_t& val_size) : values()
{
	FOR(val_size)
	{
		push(*val);
		val++;
	}
}

template <class T>
stack<T>::stack(const stack<T>& s)
{
	this->values = s.values;
}

template <class T>
stack<T>::stack(const stack<T>&& s)
{
	this->values = s.values;
}

//------------------------------------------------
// modifier methods:

template <class T>
stack<T>& stack<T>::operator = (const stack<T>& s)
{
	this->values = s.values;
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
bool stack<T>::operator == (const stack<T>& s) const
{
	return this->values == s.values;
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
