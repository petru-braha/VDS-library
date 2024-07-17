#pragma once
#include "tree.h"
#include <initializer_list>

template <class T = int>
class minheap : public tree<T, node_bint<T>>
{
	// typedef:
	typedef const T& type;
	typedef node_bint<T>* ptr;

	// iterator concept:
	class iterator 
	{
		static size_t n;
		size_t index;
		T bfs_nodes;
	public:
		iterator(const minheap<T>& h);
		iterator(void* ptr = nullptr);
		~iterator();

		T		operator * () const;
		void	operator ++();
		bool	operator !=(const iterator& two) const;
	};

	// auxiliar utility:
	void heapify(ptr& node);
	void arrange(ptr& node = root);
public:
	bool (*f)(type, type);
	// constructors:
	minheap(const T& value = NULL);
	minheap(const std::initializer_list<T>& val, bool (*f)(type, type) = nullptr);
	minheap(T* val, const size_t& val_size, bool (*f)(type, type) = nullptr);
	minheap(const minheap<T>& h);
	minheap(const minheap<T> && h);
	~minheap();
	
	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// specific methods:
	minheap<T>& operator = (const minheap<T>& h);
	void insert(const T& value);
	void extrct(); 
	bool search(const T& value) const;

	// constant methods:
	bool operator == (const minheap<T>& h) const;
	size_t getn() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions:
	friend T* convert(const minheap<T>& h);
	friend std::ostream& operator << (std::ostream& out, const minheap<T>& h);
};

// comments:
// bfs traversal

template<class T>
size_t minheap<T>::iterator::n = 0;

/*
template <class T>
void swap(node_tree<T>*& one, node_tree<T>*& two)
{
	T temp = one->get();
	one->get() = two->get();
	two->get() = temp;
}

template <class T>
void minheap<T>::heapify(ptr& node)
{
	node_tree<T>* node_largest = node, node_left = node->left, node_rght = node->rght;
	if (node_left && f(node_left->get(), node_largest->get()))
		node_largest = node_left;
	if (node_rght && f(node_rght->get(), node_largest->get()))
		node_largest = node_rght;

	if (node_largest != node)
	{
		swap(node, node_largest);
		heapify(node_largest);
	}
}

template <class T>
void minheap<T>::arrange(node_tree<T>*& node)
{
	if (node == nullptr)
		return;
	arrange(node->rght); // 1 3 2 is not sorted; starting with left
	arrange(node->left);
	if (node->left) // if it is a parent
		heapify(node);
}

//------------------------------------------------
// constructors:

template <class T>
minheap<T>::~minheap()
{
	clear();
}

template <class T>
minheap<T>::minheap(const T& value) : tree<T>(value)
{
	f = [](type x, type y)->bool { return x < y; }; // compare this with maxheap's lambda
};

template <class T>
minheap<T>::minheap(const std::initializer_list<T>& val, bool (*f)(type, type))
{
	if((this->f = f) == nullptr) this->f = [](type x, type y)->bool { return x < y; };
	if (val.size() < 1)
	{
		root = new ptr;
		return;
	}

	bool direction = left_child;
	root = new ptr(*val.begin());
	queue<ptr> initialised_nodes = { root };

	for (auto it = val.begin() + 1; it < val.end(); it++)
	{
		T value = *it;
		ptr node = new ptr(value);

		ptr actual = initialised.front();
		if (direction == left_child)
		{
			actual->left = node;
			direction = rght_child;
		}
		else //(direction == rght_child)
		{
			actual->rght = node;
			direction = left_child;
		}

		if (actual->left && actual->rght)
			initialised.pop();
		initialised.push(node);
	}
	arrange();
}

template <class T>
minheap<T>::minheap(T* val, const size_t& val_size, bool (*f)(type, type))
{
	if ((this->f = f) == nullptr) this->f = [](type x, type y)->bool { return x < y; };
	if (val_size < 1)
	{
		root = new ptr;
		return;
	}

	bool direction = left_child;
	root = new ptr(val[0]);
	queue<ptr> initialised_nodes = { root };

	for (auto it = 1; it < val_size; it++)
	{
		T value = val[it];
		ptr node = new ptr(value);

		ptr actual = initialised.front();
		if (direction == left_child)
		{
			actual->left = node;
			direction = rght_child;
		}
		else //(direction == rght_child)
		{
			actual->rght = node;
			direction = left_child;
		}

		if (actual->left && actual->rght)
			initialised.pop();
		initialised.push(node);
	}
	arrange();
}

template <class T>
minheap<T>::minheap(const minheap<T>& h)
{
	if ((this->f = h.f) == nullptr) this->f = [](type x, type y)->bool { return x < y; };
	if (h.n < 1)
		return;

	bool direction = left_child;
	root = new ptr(h.root->get());
	queue<ptr> initialised_nodes = { root };

	for (auto it = h.begin() + 1; it != h.end(); it++)
	{
		T value = *it;
		ptr node = new ptr(value);

		ptr actual = initialised.front();
		if (direction == left_child)
		{
			actual->left = node;
			direction = rght_child;
		}
		else //(direction == rght_child)
		{
			actual->rght = node;
			direction = left_child;
		}

		if (actual->left && actual->rght)
			initialised.pop();
		initialised.push(node);
	}
}

template <class T>
minheap<T>::minheap(const minheap<T>&& h)
{
	if ((this->f = h.f) == nullptr) this->f = [](type x, type y)->bool { return x < y; };
	if (h.n < 1)
		return;

	bool direction = left_child;
	root = new ptr(h.root->get());
	queue<ptr> initialised_nodes = { root };

	for (auto it = h.begin() + 1; it != h.end(); it++)
	{
		T value = *it;
		ptr node = new ptr(value);

		ptr actual = initialised.front();
		if (direction == left_child)
		{
			actual->left = node;
			direction = rght_child;
		}
		else //(direction == rght_child)
		{
			actual->rght = node;
			direction = left_child;
		}

		if (actual->left && actual->rght)
			initialised.pop();
		initialised.push(node);
	}
	h.clear();
}

//------------------------------------------------
// iterator methods:

template <class T>
minheap<T>::iterator::iterator(const minheap<T>& h)
{
	this->n = h.n;
	this->bfs_nodes = new T[n];

	queue<ptr> nodes = { h.root };
	while (!nodes.empty())
	{
		int original_size = nodes.get_size();

		// add to queue, action until original_size, and then remove
		FOR(original_size)
		{
			node_tree<T>* node = nodes.front();
			this->bfs_nodes[index++] = node->get();

			if (node->left) nodes.push(node->left);
			if (node->rght) nodes.push(node->rght);
			nodes.pop();
		}
	}

	this->index = 0;
}

template <class T>
minheap<T>::iterator::iterator(void* ptr)
{
	index = n = bfs_nodes = NULL;
}

template <class T>
minheap<T>::iterator::~iterator()
{
	if (bfs_nodes)
		delete[]bfs_nodes;
}

template <class T>
T minheap<T>::iterator::operator * () const
{
	return bfs_nodes[index];
}

template <class T>
void minheap<T>::iterator::operator ++ ()
{
	index++;
}

template <class T>
bool minheap<T>::iterator::operator != (const iterator& two) const
{
	return index == n;
}

template <class T>
typename minheap<T>::iterator minheap<T>::begin() const
{
	return iterator(*this);
}

template <class T>
typename minheap<T>::iterator minheap<T>::end() const
{
	return iterator(nullptr);
}

//------------------------------------------------
// specific methods:

template <class T>
minheap<T>& minheap<T>::operator = (const minheap<T>& h)
{
	if ((this->f = h.f) == nullptr) this->f = [](type x, type y)->bool { return x < y; };
	if (h.n < 1)
		return;
	this->clear();
	this = new minheap<T>(h);
	return *this;
}

template <class T>
void minheap<T>::insert(const T& value)
{
	T value_interchange = value;
	// find the category where it fits
	ptr it = root;
	while (value_interchange > it->get()) // f
	{
		// check if children exists
		if (it->left == nullptr); // they don't


		// check their value
		// find the closest value
		// change with l / r
	}
}


























//------------------------------------------------
// constant methods:

//------------------------------------------------
// friend functions:
*/
