#pragma once
#include "node/node_avlt.cpp"
#include "node/node_rb_t.cpp"

enum traversal_types
{
    bfs,
    preorder,
    inorder, 
    postorder
};

template <class T, typename node_type>
class special_binary_tree
{
protected:
    // data members:
    size_t n;
    node_type* root;
public:
    // constructors:
    special_binary_tree(const T& value);
    virtual ~special_binary_tree();
    
    // specific methods:
    void clear(node_bint<T>*& parent); // postorder
    virtual void insert(const T& value) = 0;
    //virtual node_type* search(const T& value) const = 0;

    // constant methods:
    //size_t getn() const;
    //void   prnt(ptr& parent = root, const short& traversal_method = inorder) const;
    //bool  empty() const;
    //size_t height(ptr& parent = root) const;
    
    // friend functions:
    //friend void* collection_ptr(const special_binary_tree<T, node_type>& t); // just for the collection!
};

// comments:
// no << operator and no convert method:
// minheap is traversed bfs and binary search tree use inorder traversal