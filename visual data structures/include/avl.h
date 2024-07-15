#pragma once
#include "tree.h"

template <class T = int>
class avl : public tree<T, node_avlt<T>>
{
	// typedef:
	typedef node_avlt<T>* ptr;
	
	// auxiliar methods:
	ptr left_rotation(ptr& node);
	ptr rght_rotation(ptr& node);
public:
	// constructors:
	avl(const T& value = NULL);
	~avl();

	// specific methods:
	void insert(const T& value);
	void remove(const T& value);

	// query operations:
	ptr    search(const T& value) const;
	size_t height(ptr& parent) const;
	//T minimum() const;
	//T maximum() const;
	//T predcessr(const T& value) const;
	//T successor(const T& value) const;

	// constant methods:
	//void prnt(node_type*& parent, const char& traversal_method = inorder) const;

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};

//------------------------------------------------
// auxiliar methods:

template <class T>
node_avlt<T>* avl<T>::left_rotation(ptr& node)
{
	ptr it = node->successor[rght_child];
	node->successor[rght_child] = it->successor[left_child];
	it->successor[left_child] = node;

	size_t h1 = node->successor[left_child]->get_height();
	size_t h2 = node->successor[rght_child]->get_height() + 1;
	node->set_height(h1 > h2 ? h1 : h2);

	h1 = it->successor[left_child]->get_height();
	h2 = it->successor[rght_child]->get_height() + 1;
	it->set_height(h1 > h2 ? h1 : h2);
	return it;
}

template <class T>
node_avlt<T>* avl<T>::rght_rotation(ptr& node)
{
	ptr it = node->successor[left_child];
	node->successor[left_child] = it->successor[rght_child];
	it->successor[rght_child] = node;

	size_t h1 = node->successor[left_child]->get_height();
	size_t h2 = node->successor[rght_child]->get_height() + 1;
	node->set_height(h1 > h2 ? h1 : h2);

	h1 = it->successor[left_child]->get_height();
	h2 = it->successor[rght_child]->get_height() + 1;
	it->set_height(h1 > h2 ? h1 : h2);
	return it;
}

//------------------------------------------------
// constructors:

template <class T>
avl<T>::avl(const T& value) : tree<T, node_avlt<T>>(value) {}

template <class T>
avl<T>::~avl() {}

//------------------------------------------------
// specific methods:

template <class T>
void avl<T>::insert(const T& value)
{
	if()
	// find its place

	// compute balance factor of its parents
	
	// treat the cases
}

template <class T>
void avl<T>::remove(const T& value);

//------------------------------------------------
// query operations:

// search
// height

//------------------------------------------------
// friend functions:

