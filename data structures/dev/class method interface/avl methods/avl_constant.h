#pragma once
#include "../abstract class methods/constant_methods.h"

template <typename argument, typename node>
class avl_constant : public constant_methods<argument>
{
	typedef const node* ptr_return;

public:
	virtual size_t get_arity() const = 0;
	virtual ptr_return get_r() const = 0;
};
