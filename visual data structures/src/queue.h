#pragma once
#include "adaptor.h"

template <class T>
class queue : public adaptor<T>
{
public:
	// constructors:
	queue();
	queue(std::initializer_list<T>& val);
	queue(T* val, const size_t& val_size);
	queue(const adaptor<T>& adp);
	queue(const adaptor<T>&& adp);
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

//------------------------------------------------
// constructors:

template <class T>
queue<T>::queue() : adaptor() {};

template <class T>
queue<T>::queue(std::initializer_list<T>& val) : adaptor(val) {};

template <class T>
queue<T>::queue(T* val, const size_t& val_size) : adaptor(val, val_size) {};

template <class T>
queue<T>::queue(const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
queue<T>::queue(const adaptor<T>&& adp)
{
	this->values = adp.values;
	delete adp;
}

//------------------------------------------------
// specific methods:

template <class T>
queue<T>& queue<T>::operator = (const adaptor<T>& adp)
{
	this->values = adp.values;
}

template <class T>
T queue<T>::front() const
{
	return values[0];
}

template <class T>
T queue<T>::back() const
{
	return values[values.getn() - 1];
}

template <class T>
void queue<T>::push(const T& val)
{
	values.insert(val);
}

template <class T>
void queue<T>::pop()
{
	values.remove(0);
}

//------------------------------------------------
// constant methods:

template <class T>
bool queue<T>::operator == (const adaptor<T>& adp) const
{
	return this->values == adp.values;
}

template <class T>
void queue<T>::prnt() const
{
	std::cout << '\n' << "front->back: ";
	for (auto i : values)
		std::cout << i << ' ';
	std::cout << '\n';
}