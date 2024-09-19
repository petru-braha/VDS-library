#pragma once

#define left_child 0
#define rght_child 1

template <class T, typename node_type, size_t arity>
class node
{
	// data members:
	mutable T data;

public:
	// auxiliar utility:
	node_type* successor[arity];
	
	// constructors:
	virtual ~node() = 0;
	node(const T& value);

	// specific methods:
	void set(const T& value) const;

	// constant methods:
	T&		get() const;
	size_t  get_arity() const;
};

//------------------------------------------------
// constructors:

template <class T, typename node_type, size_t arity>
node<T, node_type, arity>::~node() {}

template <class T, typename node_type, size_t arity>
node<T, node_type, arity>::node(const T& value)
{
	this->data = value;
	for (size_t i = 0; i < arity; i++)
		this->successor[i] = nullptr;
}

//------------------------------------------------
// specific methods:

template <class T, typename node_type, size_t arity>
void node<T, node_type, arity>::set(const T& value) const
{
	data = value;
}

//------------------------------------------------
// constant methods:

template <class T, typename node_type, size_t arity>
T& node<T, node_type, arity>::get() const
{
	return (T&)data;
}

template <class T, typename node_type, size_t arity>
size_t node<T, node_type, arity>::get_arity() const
{
	return arity;
}
