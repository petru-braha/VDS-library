#pragma once
#include "basic_iterator.h"

template <class T>
class avl_iterator : public basic_iterator<T, avl_iterator<T>>
{
	// data members:
	// stack of values;
	// flags != * ++

public:
	// constructors:
	avl_iterator(T& value);

	// specific methods:
	T		operator  * () const;
	void	operator ++ ();
	bool	operator != (const array_iterator<T>& it) const;
};

//------------------------------------------------
// constructors:

