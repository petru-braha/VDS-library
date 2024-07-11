#pragma once
#include "tree.h"
#include <initializer_list>

template <class T>
class minheap : public tree<T>
{
	typedef const T& type;

	class iterator 
	{
		T* value;
	public:
		iterator(T* val);

		T		operator * () const;
		void	operator ++();
		bool	operator !=(const iterator& two) const;
	};

	void heapify(ptr& node);
	void arrange();
public:
	bool (*f)(type, type);
	// constructors:
	minheap(const T& value = NULL);
	minheap(const std::initializer_list<T>& val, bool (*f)(type, type) = nullptr);
	minheap(T* val, const size_t& val_size, bool (*f)(type, type) = nullptr);
	minheap(const minheap(T)& h);
	minheap(const minheap(T) && h);
	~minheap();
	
	// iterator methods;
	iterator begin() const;
	iterator end() const;

	// specific methods:
	void insert(const T& value);
	void remove(const T& value);
	void search(const T& value) const;

	// constant methods:
	void prnt(ptr& parent = root, const short& traversal_method = bfs) override const;

	// friend functions:
	friend T* convert(const minheap<T>& h);
	friend std::ostream& operator << (std::ostream& out, const minheap<T>& h);
};