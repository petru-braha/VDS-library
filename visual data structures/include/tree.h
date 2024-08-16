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
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const size_t& szt;

	typedef const node_type* ptr_return;

public:
    // constructors:
	virtual ~tree() = default;
    
    // modifier methods:
    virtual void clear() = 0;
	virtual void setf(fct f) = 0;

	// query operations:
	virtual		size_t height(const node_type*& parent) const = 0;
	virtual ptr_return search(const T& value) const = 0;
	virtual ptr_return minimum() const = 0;
	virtual ptr_return maximum() const = 0;
	virtual ptr_return predcessr(const node_type*& value) const = 0;
	virtual ptr_return successor(const node_type*& value) const = 0;
	 
	// constant methods:
	virtual size_t get_arity() const = 0;
	virtual size_t		getn() const = 0;
	virtual ptr_return	getr() const = 0;
	virtual void*		getf() const = 0;
	virtual void		prnt() const = 0;
	virtual bool	   empty() const = 0;
};

// comments:
// minheap is traversed bfs and binary search tree use inorder traversal
