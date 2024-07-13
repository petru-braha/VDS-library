#pragma once
#include "special_binary_tree.cpp"

template <class T = int>
class avl : public special_binary_tree<T, node_avlt<T>>
{
	// typedef:
	//typedef node_avlt<T>* ptr_a;
	
	// auxiliar methods:
	//void left_rotation(ptr_a& node);
	//void rght_rotation(ptr_a& node);
public:
	// constructors:
	avl(const T& value = NULL);
	~avl();

	// specific methods:
	void  insert(const T& value) {}
	//void  remove(const T& value);
	//ptr_a search(const T& value) const { return false; }

	// constant methods:
	//size_t height(ptr_a& node = root) const;

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};
