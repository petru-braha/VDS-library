#pragma once
#include "special_binary_tree.h"

template <class T = int>
class red_black_tree : special_binary_tree<T, node_rb_t<T>>
{
	typedef node_rb_t<T>* ptr;

	// auxiliar methods:
	void left_rotation(ptr& node);
	void rght_rotation(ptr& node);
public:
	// constructors:
	red_black_tree(const T& value);
	~red_black_tree();

	// specific methods:
	void insert(const T& value);
	void remove(const T& value);
	bool search(const T& value);

	// constant methods:
	size_t height(ptr& node);

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};
