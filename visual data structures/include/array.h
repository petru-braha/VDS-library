#pragma once
#include "bureaucracy.h"
#include "array_sorting.h"
#include <initializer_list>

#define default_array_size 100

template <class T = int>
class array
{
	size_t n;	// its purpose is just to allocate space
	size_t last;// gurantees that elements selected by user are initialised contiguously // index of the last concrete value
	T* values;

	class iterator
	{
		T* value;
	public:
		iterator(T* val);

		T		operator*() const;
		void	operator++();
		bool	operator!=(const iterator& two) const;
	};

	void shift_left(const size_t& left_position);
public:
	// constructors:
	array(const int& n = default_array_size);
	array(const std::initializer_list<T>& val, const size_t& n = default_array_size);
	array(T* val, const size_t& val_size, const size_t& n = default_array_size);
	array(const array<T>& arr);
	array(const array<T>&& arr);
	~array();

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// specific methods:
	array<T>& operator = (const array<T>& arr);
	void sort(const int& algorithm = quick_sort, bool (*f)(const T&, const T&) = nullptr);
	void insert(const T& value, const size_t& index = last + 1);
	void remove(const size_t& index);
	void remove(const T& value, const bool& all = false);
	bool search(const T& value) const; // used for crossng

	// constant methods:
	bool operator == (const array<T>& arr) const;
	T& operator [] (const size_t& index) const; // get / replace method, shift to the left until there is no more empty space
	size_t getn() const;
	size_t getl() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions:
	friend T* convert(const array<T>& arr);
	friend array<T> linking(const array<T>& one, const array<T>& two);
	friend void		ejectin(const array<T>& one, const array<T>& two);
	friend array<T> crossng(const array<T>& one, const array<T>& two);
	friend std::ostream& operator << (std::ostream& out, const array<T>& arr);
};

