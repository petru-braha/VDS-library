#pragma once
#include "linked_list.h"
#include "interface/adaptor.h"
#include <initializer_list>

template <class T = int>
class queue : public adaptor<T>
{	
public:
	// constructors:
	~queue() = default;
	queue();
	queue(const std::initializer_list<T>& data);
	queue(const T* data, const size_t& data_size);
	queue(const queue<T>& q);
	queue(const queue<T>&& q);

	// modifier methods:
	queue<T>& operator = (const queue<T>& q);
	
	// specific methods:
	queue<T>& push(const T& value);
	queue<T>& pop();

	// constant methods:
	T	 front() const;
	T	 back() const;
	bool operator == (const queue<T>& q) const;
	size_t get_n() const;
	bool   empty() const;

private:
	// data members:
	linked_list<T> values;
};

//------------------------------------------------
// constructors:

template <class T>
queue<T>::queue() : values() {}

template <class T>
queue<T>::queue(const std::initializer_list<T>& data) : values(data) {}

template <class T>
queue<T>::queue(const T* data, const size_t& data_size) : values(data, data_size) {}

template <class T>
queue<T>::queue(const queue<T>& q) : values(q.values) {}

template <class T>
queue<T>::queue(const queue<T>&& q) : values(q.values) {}

//------------------------------------------------
// modifier methods:

template <class T>
queue<T>& queue<T>::operator = (const queue<T>& q)
{
	this->values = q.values;
}

//------------------------------------------------
// specific methods:

template <class T>
queue<T>& queue<T>::push(const T& value)
{
	node_list<T> ptr(value);
	auto c_tail = values.get_tail();
	auto tail = const_cast<node_list<T>*>(c_tail);
	values.insert(&ptr, tail);
	return *this;
}

template <class T>
queue<T>& queue<T>::pop()
{
	if(empty())
		hard_error("no data");
	values.remove(linked_list<T>::head_node);
	return *this;
}

//------------------------------------------------
// constant methods:

template <class T>
T queue<T>::front() const
{
	if (empty())
		hard_error("no data");
	return values.get_head()->get();
}

template <class T>
T queue<T>::back() const
{
	if (empty())
		hard_error("no data");
	return values.get_tail()->get();
}

template <class T>
bool queue<T>::operator == (const queue<T>& q) const
{
	return this->values == q.values;
}

template <class T>
size_t queue<T>::get_n() const
{
	return values.get_n();
}

template <class T>
bool queue<T>::empty() const
{
	return values.empty();
}
