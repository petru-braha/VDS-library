#pragma once
#include "../abstract class methods/specific_methods.h"

template <typename node>
class avl_specific : public specific_methods
{
public:
	virtual avl_specific& insert(const node* const value) = 0;
	virtual avl_specific& remove(const node* const value) = 0;
};
