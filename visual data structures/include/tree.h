#pragma once
#include "bureaucracy.h"
#include "node/node_avlt.h"
#include "node/node_rb_t.h"
// #include "queue.cpp" // for bfs traversal

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
protected:
    // data members:
    size_t n, arity;
    node_type* root;
public:
    // constructors:
	virtual ~tree();
	tree(const T& value);
    
    // specific methods:
    void clear(node_type*& parent); // postorder

	// query operations:
    virtual node_type* search(const T& value) const = 0;
	virtual     size_t height(node_type*& parent) const;
	//virtual T minimum() const = 0;
	//virtual T maximum() const = 0;
	//virtual T predcessr(const T& value) const = 0;
	//virtual T successor(const T& value) const = 0;

    // constant methods:
	size_t get_arity() const;
	size_t getn() const;
	void   prnt(node_type*& parent, const char& traversal_method) const;
    bool  empty() const;
    
    // friend functions:
    //friend void* collection_ptr(const special_binary_tree<T, node_type>& t); // just for the collection!
};

// comments:
// no specific functions: each class needs other types of signatures
// no << operator and no convert method:
// minheap is traversed bfs and binary search tree use inorder traversal

//------------------------------------------------
// constructors:

template <class T, typename node_type>
tree<T, node_type>::~tree()
{
	clear(root);
}

template <class T, typename node_type>
tree<T, node_type>::tree(const T& value)
{
	n = 1;
	root = new node_type(value);
	this->arity = root->get_arity();
}

//------------------------------------------------
// specific methods:

template <class T, typename node_type>
void tree<T, node_type>::clear(node_type*& parent)
{
	if (parent == nullptr)
		return;
	FOR(this->arity)
		clear(parent->successor[i]);

	delete parent;
	parent = nullptr;
	n--;
}

//------------------------------------------------
// query operations:

template <class T, typename node_type>
size_t tree<T, node_type>::height(node_type*& parent) const
{
	if (parent == nullptr)
		return 0;

	size_t maximum_height = -1;
	FOR(parent->nr_children())
	{
		size_t h = heght(parent->children[i]);
		maximum_height = maximum_height > h ? maximum_height : h;
	}
	return 1 + maximum_height;
}

//------------------------------------------------
// constant methods:

template <class T, typename node_type>
size_t tree<T, node_type>::getn() const
{
	return n;
}

template <class T, typename node_type>
size_t tree<T, node_type>::get_arity() const
{
	return arity;
}

template <class T, typename node_type>
void tree<T, node_type>::prnt(node_type*& parent, const char& traversal_method) const
{
	if (parent == nullptr)
		return;

	switch (traversal_method)
	{
	case bfs:
		queue<node_special_binary_tree<T>*> nodes = parent;
		while (!nodes.empty())
		{
			int original_size = nodes.get_size();

			// add to queue, action until original_size, and then remove
			FOR(original_size)
			{
				node_special_binary_tree<T>* node = nodes.front();
				std::cout << node->get() << ' ';
				FOR(node->nr_children())
					if (node->children[i]) // patch
						nodes.push(node->children[i]);
				nodes.pop();
			}
		}
		break;

	case preorder:
		std::cout << parent->get() << ' ';
		for (size_t i = 0; i < parent->nr_children(); i++)
			prnt(parent->children[i], traversal_method);
		break;

	case inorder:
		for (size_t i = 0; i < parent->nr_children() - 1; i++)
			prnt(parent->children[i], traversal_method);
		std::cout << parent->get() << ' ';
		std::cout << parent->children[parent->nr_children() - 1]->get() << ' ';
		break;

	case postorder:
		for (size_t i = 0; i < parent->nr_children(); i++)
			prnt(parent->children[i], traversal_method);
		std::cout << parent->get() << ' ';
		break;
	default:
		break;
	}
}

template <class T, typename node_type>
bool tree<T, node_type>::empty() const
{
	return n == 0;
}

//------------------------------------------------
// friend functions:

template <class T, typename node_type>
void* collection_ptr(const tree<T, node_type>& t)
{
	return (void*)t.root;
}
