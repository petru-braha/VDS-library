#pragma once
#include "pch.h"
#include "trivial_tree.h"

template <class T>
bool trivial_tree<T>::complete(ptr& parent) const
{
	if (parent == nullptr)
		return true;
	bool result = true;

	for (size_t i = 0; i < parent->nr_children() - 1; i++)
	{
		result = (result && complete(parent->children[i], traversal_method);
		if (result == false)
			return false;
	}
	if (complete_individual_check(parent, root->nr_children()) == false)
		return false;
	if (parent->children[parent->nr_children() - 1]->nr_children() != root->nr_children())
		return false;
	return true;
}

