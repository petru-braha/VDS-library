#pragma once
#include "pch.h"
#include "../include/array.h"

//------------------------------------------------
// constructors:

template <class T>
array<T>::~array()
{
	delete[]values;
}

template <class T>
array<T>::array(const int& n)
{
	this->n = n;
	last = -1;
	values = new T[n];
	for (size_t i = 0; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const std::initializer_list<T>& val, const size_t& n)
{
	if (val.size() > n)
		hard_error("wrong parameters");
	this->n = n;
	last = val.size() - 1;
	values = new T[n]; 
	
	size_t index = 0;
	for (auto i : val)
		values[index++] = i;
	for (; index < n; index++)
		values[index] = NULL;
}

template <class T> 
array<T>::array(T* val, const size_t& val_size, const size_t& n)
{
	size_t index = 0;
	this->n = n;
	this->last = -1;
	while (index < val_size)
	{
		values[++last] = *val;
		val++;
		index++;
	}

	for (size_t i = last + 1; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const array<T>& arr)
{
	this->n = arr.getn();
	values = new T[n];
	
	for (auto i : arr)
		this->values[this->last++] = i;
	this->last--;
	for (size_t i = last + 1; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const array<T>&& arr)
{
	this->n = arr.getn();
	values = new T[n];

	for (auto i : arr)
		this->values[this->last++] = i;
	this->last--;
	for (size_t i = last + 1; i < n; i++)
		values[i] = NULL;
	delete arr;
}

//------------------------------------------------
// iterator methods:

template <class T>
array<T>::iterator::iterator(T* val)
{
	this->value = val;
}

template <class T>
T array<T>::iterator::operator*() const
{
	return *value;
}

template <class T>
void array<T>::iterator::operator++()
{
	value++;
}

template <class T>
bool array<T>::iterator::operator != (const iterator& two) const
{
	return (value != two.value);
}

template <class T>
typename array<T>::iterator array<T>::begin() const
{
	return iterator(&values[0]);
}

template <class T>
typename array<T>::iterator array<T>::end() const
{
	return iterator(&values[last+1]);
}

//------------------------------------------------
// specific methods:

template <class T>
array<T>& array<T>::operator = (const array<T>& arr)
{
	this->n = arr.n;
	this->last = -1;
	delete[]this->values;
	this->values = new T[n];
	for (auto i : arr)
		this->values[++last] = i;
}

#include "array_sorting.cpp"
template <class T>
void array<T>::sort(const int& algorithm, bool (*f)(const T&, const T&))
{
	array_sorting<T>* sort_job = array_sorting<T>::get_instance();
	switch (algorithm)
	{
	case bubble_sort:
		sort_job->bubbs(values, last + 1, f);
		break;
	case selection_sort:
		break;
	case insertion_sort:
		break;
	case merge_sort:
		break;
	case heap_sort:
		sort_job->heaps(values, last + 1, f);
		break;
	case quick_sort:
		sort_job->qucks(values, 0, last, f);
		break;
	default:
		break;
	}
}

template <class T>
void array<T>::shift_left(const size_t& left_position)
{
	if (empty())
		eazy_error("nothing to shift");
	if (left_position)
		left_position--;
	for (size_t i = left_position; i < last; i++)
		values[i] = values[i + 1];
	values[last--] = NULL;
}

template <class T>
T& array<T>::operator [] (const size_t& index) const
{
	if (index >= n)
		hard_error("bad index");
	if (index > last)
	{
		hard_error("unallocated space"); // the user has to use insert, for adding a new value, not this operator
		return values[last + 1];
	}

	return values[index];
};

template <class T>
void array<T>::insert(const T& value, const size_t& index)
{
	if (index > n || index < 0)
		hard_error("bad index");
	if (index > last)
	{
		values[++last] = value;
		return;
	}
	
	if (last + 1 >= n)
	{
		eazy_error("no more memory")
		return;
	}

	for (size_t i = last + 1; i > index; i--) // shift right
		values[i] = values[i - 1];
	values[index] = value;
}

template <class T>
void array<T>::remove(const size_t& index)
{
	if (empty())
		return;
	if (index > n)
		hard_error("bad index");
	if (index <= last)
		shift_left(index + 1);
}

template <class T>
void array<T>::remove(const T& value, const bool& all)
{
	for (size_t i = 0; i <= last; i++)
		if (values[i] == value)
		{
			shift_left(i + 1);
			if (all == false)
				return;
			i--;
		}
}

template <class T>
bool array<T>::search(const T& value) const
{
	for (auto i : *this)
		if (i == value)
			return true;
	return false;
}

//------------------------------------------------
// constant methods:

template <class T>
bool array<T>::operator == (const array<T>& arr) const
{
	if (this->n != arr.n)
		return false;
	if (this->last != arr.last)
		return false;
	for (size_t i = 0; i < last + 1; i++)
		if (values[i] != arr[i])
			return false;
	return true;
}

template <class T>
size_t array<T>::getn() const
{
	return n;
}

template <class T>
size_t array<T>::getl() const
{
	return last;
}

template <class T>
void  array<T>::prnt() const
{
	FOR(n)
		std::cout << values[i] << ' ';

}

template <class T>
bool array<T>::empty() const
{
	return last == -1;
}

//------------------------------------------------
// friend functions:

template <class T>
T* convert(const array<T>& arr)
{
	T* ptr = new T[arr.last + 1];
	FOR(arr.last + 1)
		ptr[i] = arr[i];
	return ptr;
}

template <class T>
array<T> linking(const array<T>& one, const array<T>& two)
{
	size_t new_n = one.getn() + two.getn();	
	array<T> new_array(new_n);
	for (auto i : one)
		new_array.insert(i);
	for (auto i : two)
		new_array.insert(i);
	return new_array;
}

template <class T>
void ejectin(const array<T>& one, const array<T>& two)
{
	for (auto i : two)
		one.remove(i, true);
}

template <class T>
array<T> crossng(const array<T>& one, const array<T>& two) // O(n*m), n = |one|, m = |two|. can be done in O(n + m) with a hash table
{
	array<T> new_array = (one.getn() + two.getn());
	if (one.getl() < two.getl())
	{
		for (auto key : two)
			if (one.search[key])
				new_array.insert(key);
	}
	else
	{
		for (auto key : one)
			if (two.search[key])
				new_array.insert(key);
	}

	return new_array;
}

template <class T>
std::ostream& operator << (std::ostream& out, const array<T>& arr)
{
	for (auto i : arr)
		out << i << ' ';
	return out;
}

