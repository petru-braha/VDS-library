#pragma once
#include "node/node_tree.h"

template <class T>
class trivial_tree // designed to have more control over a fictive tree
{
	typedef node_tree<T>* ptr;
protected:
	short arity;
	size_t n;
	ptr root;
public:
	// constructors

	// specific methods:
	trivial_tree<T>& operator = (const trivial_tree<T>& t);
	void insert(ptr& parent, const size_t& index_child, const T& value, const short& arity = 2);
	void remove(ptr& parent, const size_t& index_child);
	ptr  search(const T& value) const;

	// constant methods:
	bool   operator == (const trivial_tree<T>& t); // bfs 
	size_t getn() const;
	short  get_arity() const;
	void   prnt(ptr& parent = root, const short& traversal_method = inorder) const;
	bool   empty() const;
	
	size_t height(ptr& parent = root) const;
	bool complete(ptr& parent = root) const;
};

