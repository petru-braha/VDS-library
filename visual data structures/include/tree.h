#pragma once
#include "node/node_tree.h"

enum
{
    bfs,
    preorder,
    inorder, // default
    postorder
};

template <class T = int>
class tree // designed to be complete
{
    typedef node_tree<T>* ptr;
protected:
    short arity;
    size_t n;
    ptr root;
public:
    // constructors:
    tree();
    tree(const std::initializer_list<T>& val, const short& traversal_method = bfs);
    tree(T* val, const short& traversal_method = bfs);
    tree(const tree<T>& t);
    tree(const tree<T>&& t);
    ~tree();

    // specific methods:
    tree<T>& operator = (const tree<T>& t); // bfs
    void  clear(ptr& node = root); // postorder
    virtual void insert(const T& value);
    virtual void remove(const T& value);
    ptr  search(const T& value) const;

    // constant methods:
    bool   operator == (const tree<T>& t); // bfs 
    size_t getn() const;
    short  get_arity() const;
    void   prnt(ptr& parent = root, const short& traversal_method = inorder) const;
    bool   empty() const;
    size_t height(ptr& parent = root) const;
};