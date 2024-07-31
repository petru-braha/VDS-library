#pragma once
#include "list.h"
#include "adaptor.h"

template <class T>
class queue : public adaptor<T>
{
	// data members:
	list<T> values;
public:
	// constructors:
	~queue() = default;
	queue();
	queue(std::initializer_list<T>& val);
	queue(T* val, const size_t& val_size);
	queue(const adaptor<T>& adp);
	queue(const adaptor<T>&& adp);

	// modifier methods:
	queue<T>& operator = (const adaptor<T>& adp);
	
	// specific methods:
	T	 front() const;
	T	 back() const;
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
queue<T>::queue() : values() {};

template <class T>
queue<T>::queue(std::initializer_list<T>& val) : values() 
{
	for (auto key : val)
		push(key);
};

template <class T>
queue<T>::queue(T* val, const size_t& val_size) : values() 
{
	FOR(val_size)
	{
		push(*val);
		val++;
	}
}

template <class T>
queue<T>::queue(const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
queue<T>::queue(const adaptor<T>&& adp)
{
	this->values = adp.values;
}

//------------------------------------------------
// modifier methods:

template <class T>
queue<T>& queue<T>::operator = (const adaptor<T>& adp)
{
	this->values = adp.values;
}

//------------------------------------------------
// specific methods:

template <class T>
T queue<T>::front() const
{
	return values.frst;
}

template <class T>
T queue<T>::back() const
{
	return values.last;
}

template <class T>
void queue<T>::push(const T& val)
{
	values.atypical_insert(val, 0);
}

template <class T>
void queue<T>::pop()
{
	values.atypical_remove(0);
}

//------------------------------------------------
// constant methods:

template <class T>
bool queue<T>::operator == (const adaptor<T>& adp) const
{
	return this->values == adp.values;
}

template <class T>
size_t queue<T>::getn() const
{
	return values.n;
}

template <class T>
bool queue<T>::empty() const
{
	return values.empty();
}
