#pragma once
#include <initializer_list>
#include "bureaucracy.h"
#include "array_sorting.h"

#define default_array_size 100

template <class T = int>
class iterator
{
	T* value;
public:
	iterator(T*& val);
	
	T		operator*();
	void	operator++();
	bool	operator!=(const iterator& two);
};

template <class T = int>
class array
{
	size_t n;	// its purpose is just to allocate space
	size_t last;// gurantees that elements selected by user are initialised contiguously // index of the last concrete value
	T* values;

	void shift_left(const size_t& left_position);
public:
	// constructors
	array(const int& n = default_array_size);
	array(const std::initializer_list<T>& val, const size_t& n = default_array_size);
	array(T* val, const size_t& n = default_array_size);
	array(const array<T>& arr);
	array(const array<T>&& arr);
	~array();

	// iterator methods
	iterator<T> begin() const;
	iterator<T> end() const;

	// specific methods
	void sort(const int& algorithm = quick_sort, bool (*f)(const T&, const T&) = nullptr);
	void replce(const size_t& index, const T& value);
	void insert(const T& value);
	void remove(const size_t& index);
	void remove(const T& value, const bool& all = false);
	bool search(const T& value) const; // used for crossng

	// constant methods
	T& operator [] (const size_t& index) const; // shift to the left until there is no more empty space
	size_t getn() const;
	size_t getl() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions
	friend array<T> linking(const array<T>& one, const array<T>& two);
	friend array<T> ejectin(const array<T>& one, const array<T>& two);
	friend array<T> crossng(const array<T>& one, const array<T>& two);
};

