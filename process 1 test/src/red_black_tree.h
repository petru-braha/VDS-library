#pragma once
#include "tree.h"

template <class T = int>
class red_black_tree : tree<T, node_rb_t<T>>
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const size_t& szt;
	
	typedef node_rb_t<T>* ptr;
	typedef const node_avlt<T>*& ptr_ref;
	typedef const node_avlt<T>* ptr_return;

	// auxiliar utility:
	ptr left_rotation(ptr& node);
	ptr rght_rotation(ptr& node);
public:
	// constructors:
	~red_black_tree();
	red_black_tree();
	red_black_tree(const std::initializer_list<T>& val);
	red_black_tree(const T* val, szt val_size);
	red_black_tree(const red_black_tree<T>& t);
	red_black_tree(const red_black_tree<T>&& t);

	// iterator methods:
	iterator begin() const;
	iterator end() const;
	
	// modifier methods:
	red_black_tree<T>& operator = (const red_black_tree<T>& t);
	void clear();
	void setf(fct f);

	// specific methods:
	void insert(const ptr& value);
	void remove(const ptr& value);

	// query operations:
	size_t height(ptr_ref parent) const;
	ptr_return search(const T& value) const;
	ptr_return minimum() const;
	ptr_return maximum() const;
	ptr_return predcessr(ptr_ref value) const;
	ptr_return successor(ptr_ref value) const;

	// constant methods:
	bool operator == (const avl<T>& t);
	size_t get_arity() const;
	size_t		getn() const;
	ptr_return	getr() const;
	void*		getf() const;
	void		prnt() const;
	bool	   empty() const;

	// friend functions:
	friend T* convert(const avl<T>& t);
	friend std::ostream& operator << (std::ostream& out, const avl<T>& t);
};


