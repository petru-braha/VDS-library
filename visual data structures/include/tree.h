#pragma once
#include "node/node_tree.h"

enum traversal_types
{
    bfs,
    preorder,
    inorder, // default
    postorder
};

template <class T = int>
class tree
{
protected:
    typedef node_tree<T>* ptr;
    
    size_t n;
    ptr root;
public:
    // constructors:
    tree(const T& value = NULL);
    virtual ~tree();

    // specific methods:
    void  clear(ptr& parent = root); // postorder
    virtual void insert(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual ptr  search(const T& value) const = 0;

    // constant methods:
    size_t getn() const;
    void   prnt(ptr& parent = root, const short& traversal_method = inorder) const;
    bool   empty() const;
    size_t height(ptr& parent = root) const;
    void*  collection_ptr() const; // just for the collection!
};
