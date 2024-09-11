#pragma once
#include "../abstract class methods.h/specific_methods.h"

template <class T, typename node>
class linked_list_specific : public specific_methods
{
public:
	virtual linked_list_specific& sort() = 0;
	virtual linked_list_specific& insert(const node* const value, node* const pointer) = 0;
	virtual linked_list_specific& remove(node* pointer) = 0;
};
