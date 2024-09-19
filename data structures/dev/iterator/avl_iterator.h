#pragma once
#include "dev/bureaucracy.h"
#include "basic_iterator.h"
#include "dev/node/node_avlt.h"
#include "stack.h"

template <class T>
class avl_iterator : public basic_iterator<T, avl_iterator<T>>
{
	// data members:
	mutable node_avlt<T>* curent;
	mutable stack<node_avlt<T>*> nodes;
	mutable bool comparison_op, dereference_op;

public:
	// constructors:
	avl_iterator(node_avlt<T>* const value);
	avl_iterator();

	// specific methods:
	bool	operator != (const avl_iterator<T>& it) const;
	T		operator  * () const;
	void	operator ++ ();
};

//------------------------------------------------
// constructors:

template <class T>
avl_iterator<T>::avl_iterator(node_avlt<T>* const value) : nodes()
{
	curent = value;
	comparison_op = dereference_op = false;
}

template <class T>
avl_iterator<T>::avl_iterator() : nodes()
{
	curent = nullptr; 
	comparison_op = dereference_op = false;
}

//------------------------------------------------
// specific methods:

template <class T>
bool avl_iterator<T>::operator != (const avl_iterator<T>& it) const
{
	comparison_op = true;
	return (curent || !nodes.empty());
}

template <class T>
T avl_iterator<T>::operator * () const
{
	if (false == comparison_op)
	{
		avl_iterator<T> dummy{};
		if (false == (*this != dummy))
			hard_error("error - iterator: wrong order or operations");
	}

	comparison_op = false; 
	dereference_op = true;

	while (curent)
	{
		nodes.push(curent);
		curent = curent->successor[left_child];
	}

	curent = nodes.top();
	nodes.pop();
	return curent->get();
}


template <class T>
void avl_iterator<T>::operator ++ ()
{
	if (false == dereference_op)
		*(*this);
	dereference_op = false;

	curent = curent->successor[rght_child];
}
