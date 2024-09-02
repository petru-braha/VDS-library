#pragma once
#include "../abstract class methods.h/specific_methods.h"

template <typename node>
class avl_specific : public specific_methods
{
	typedef node* ptr;

public:
	virtual ptr insert(ptr& parent, const node* const value) = 0;
	virtual ptr remove(ptr& parent, const node* const value) = 0;
};
