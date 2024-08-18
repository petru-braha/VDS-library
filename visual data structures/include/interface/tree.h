#pragma once
#include "bureaucracy.h"
#include "node/node_bint.h"
#include "node/node_avlt.h"
#include "node/node_rb_t.h"

enum traversal_types
{
    bfs,
    preorder,
    inorder, 
    postorder
};

template <class T, typename node_type>
class tree
{
	// typedefs:
	typedef const node_type* ptr_return;

public:
    // constructors:
	virtual ~tree() = default;

	// constant methods:
	virtual size_t get_arity() const = 0;
	virtual ptr_return	getr() const = 0;
    
	// query operations:
	virtual		size_t height(const node_type*& parent) const = 0;
	virtual ptr_return search(const T& value) const = 0;
	virtual ptr_return minimum() const = 0;
	virtual ptr_return maximum() const = 0;
	virtual ptr_return predcessr(const node_type*& value) const = 0;
	virtual ptr_return successor(const node_type*& value) const = 0;
};

// comments:
// minheap is traversed bfs and binary search tree use inorder traversal
