#pragma once
#include "node/node_trivial_tree.h"

enum traversal_types
{
    bfs,
    preorder,
    inorder, // default
    postorder
};

template <class T>
class trivial_tree // designed to have more control over a fictive tree
{
	typedef node_trivial_tree<T>* ptr;
protected:
	size_t n;
	ptr root;
public:
    // constructors:
    trivial_tree();
	trivial_tree(const std::initializer_list<T>& val, const short& traversal_method = bfs, const short& arity = 2);
	trivial_tree(T* val, const short& traversal_method = bfs, const short& arity = 2);
	trivial_tree(const tree<T>& t);
	trivial_tree(const tree<T>&& t);
    ~trivial_tree();


	// specific methods:
	trivial_tree<T>& operator = (const trivial_tree<T>& t);
    void  clear(ptr& parent = root);
    void insert(ptr& parent, const size_t& index_child, const T& value, const short& arity = 2);
	void remove(ptr& parent, const size_t& index_child);
	ptr  search(const T& value, ptr& parent = root) const;

	// constant methods:
	bool   operator == (const trivial_tree<T>& t); // bfs 
	size_t getn() const;
	short  get_arity() const; // // inorder / will calculate the arity and set it accordingly
	void   prnt(ptr& parent = root, const short& traversal_method = inorder) const;
	bool   empty() const;
	
	size_t height(ptr& parent = root) const;
	bool complete(ptr& parent = root) const;
};

