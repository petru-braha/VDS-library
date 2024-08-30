#pragma once
#include "../abstract class methods.h/query_operations.h"

template <class T, typename node>
class linked_list_queries : public query_operations
{
	typedef const T& t;
	typedef const node* ptr_return;

public:
	virtual ptr_return search(t value) const = 0;
	virtual ptr_return mimimum() const = 0;
	virtual ptr_return maximum() const = 0;
	virtual ptr_return predcessr(const node*& value) const = 0;
	virtual ptr_return successor(const node*& value) const = 0;
};
