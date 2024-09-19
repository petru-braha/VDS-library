#pragma once
#include "../abstract class methods/constant_methods.h"

template <class T, typename list_typename, typename node>
class linked_list_constant : public constant_methods<list_typename>
{
	typedef const size_t& szt;
	typedef const node* ptr_return;

public:
	virtual ptr_return get_node(szt index) const = 0;
	virtual ptr_return get_head() const = 0;
	virtual ptr_return get_tail() const = 0;
};
