#pragma once
#include <initializer_list>

template <class T = int>
class iterator
{
	T* value;
public:
	iterator(T* val);
	
	T		operator*();
	void	operator++();
	bool	operator!=(const iterator& two);
};

template <class T = int>
class array
{
	friend class array_sorting;
protected:
	size_t n;	// its purpose is just to allocate space
	size_t last;// gurantees that elements selected by user are allocated contiguously // last allocated
	T* values;

	void shift_left(const size_t& left_position);
public:
	array();
	array(const int& n);
	array(const std::initializer_list<T>& val);
	array(const std::initializer_list<T>& val, const size_t& n);
	array(const array<T>& arr);
	array(const array<T>&& arr);

	// iterator 
	iterator<T> begin() const;
	iterator<T> end() const;

	// actual functions
	void sort(const int& algorithm);
	void replce(const size_t& index, const T& value);
	void insert(const T& value);
	void remove(const size_t& index);
	void remove(const T& value, const bool& all = false);

	T& operator [] (const size_t& index) const; // shift to the left until there is no more empty space
	const int getn() const;
	const int getl() const;

	// friend functions
	friend array<T> linking(const array<T>& one, const array<T>& two);
	friend array<T> ejectin(const array<T>& one, const array<T>& two);
	friend array<T> crossng(const array<T>& one, const array<T>& two);

	~array();
};

