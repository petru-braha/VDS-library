#pragma once

template <class T, typename node_type>
class bst
{
	// typedefs:
	typedef node_type* ptr;

protected:
	// auxiliar utility:
	virtual ptr left_rotation(ptr& node) = 0;
	virtual ptr rght_rotation(ptr& node) = 0;
};