#pragma once
#include "../abstract class methods.h/query_operations.h"

template <class T, typename node>
class avl_queries : public query_operations
{
	typedef const T& t;
	typedef const node* ptr_return;

public:
	virtual size_t	   height(const node* const parent) const = 0;
	virtual ptr_return search(const node* parent, t value) const = 0;
	virtual ptr_return minimum() const = 0;
	virtual ptr_return maximum() const = 0;
	virtual ptr_return predcessr(const node* value) const = 0;
	virtual ptr_return successor(const node* value) const = 0;
};
