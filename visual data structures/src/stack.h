#pragma once
#include "linked_list.h"
#include "adaptor.h"
#include <initializer_list>

template <class T = int>
class stack : public adaptor<T>
{
public:
	// constructors:
	~stack() = default;
	stack();
	stack(std::initializer_list<T>& data);
	stack(const T* data, const size_t& data_size);
	stack(const stack<T>& s);
	stack(const stack<T>&& s);

	// modifier methods:
	stack<T>& operator = (const stack<T>& s);
	
	// specific methods:
	void push(const T& value);
	void pop();

	// constant methods:
	T    top() const;
	bool operator == (const stack<T>& s) const;
	size_t get_n() const;
	bool   empty() const;

private:
	// data members:
	linked_list<T> values;
};

//------------------------------------------------
// constructors:

template <class T>
stack<T>::stack() : values() {};

template <class T>
stack<T>::stack(std::initializer_list<T>& data) : values(data) {}

template <class T>
stack<T>::stack(const T* data, const size_t& data_size) : values(data, data_size) {}

template <class T>
stack<T>::stack(const stack<T>& s) : values(s.values) {}

template <class T>
stack<T>::stack(const stack<T>&& s) : values(s.values) {}

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
void stack<T>::push(const T& value)
{
	auto ptr = new node_list<T>(value);
	values.insert(ptr, linked_list<T>::head_node);
}

template <class T>
void stack<T>::pop()
{
	if (empty())
		hard_error("no data");
	values.remove(linked_list<T>::head_node);
}

//------------------------------------------------
// constant methods:

template <class T>
T stack<T>::top() const
{
	if (empty())
		hard_error("no data");
	return values.get_head()->get();
}

template <class T>
bool stack<T>::operator == (const stack<T>& s) const
{
	return this->values == s.values;
}

template <class T>
size_t stack<T>::get_n() const
{
	return values.get_n();
}

template <class T>
bool stack<T>::empty() const
{
	return values.empty();
}
