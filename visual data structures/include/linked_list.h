#pragma once
#include "node/node_list.h"
#include <initializer_list>

template <class T>
class linked_list
{
	node_list<T>* frst, * last;
	size_t n;

	class iterator
	{
		node_list<T>* value;

	public:
		iterator(node_list<T>*& value) : value(value) {};
		T    operator  * () const { return value->get(); }
		void operator ++ () { value = value->next; }
		bool operator != (const iterator& two) const { return value != two.value; };
	};

public:
	// constructors
	linked_list();
	linked_list(const std::initializer_list<T>& val);
	linked_list(T* val);
	linked_list(const linked_list<T>& l);
	linked_list(const linked_list<T>&& l);
	~linked_list();
	
	// iterator methods
	iterator begin() const { return iterator(frst); }
	iterator end() const { return iterator(last->next); }

	// specific methods
	void insert(const T& value, const size_t& index = n);
	void remove(const T& value, const bool& all = false);
	bool search(const T& value);

	// constant methods
	T& operator[](const size_t& index) const;
	size_t getn() const;
	void   prnt() const;
	//node_list<T>* getf() const;
};
