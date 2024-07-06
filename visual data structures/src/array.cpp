#pragma once
#include "pch.h"
#include "../include/array.h"

template <class T>
array<T>::~array()
{
	delete[]values;
}

template <class T>
array<T>::array()
{
	n = default_array_size;
	last = 0;
	values = new T[n];
	for (size_t i = 0; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const int& n)
{
	this->n = n;
	last = 0;
	values = new T[n];
	for (size_t i = 0; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const std::initializer_list<T>& val)
{
	n = val.size();
	last = val.size() - 1;
	values = new T[n];

	size_t index = 0;
	for (auto i : val)
		values[index++] = i;
}

template <class T>
array<T>::array(const std::initializer_list<T>& val, const size_t& n)
{
	static_assert(n >= val.size(), "wrong parameters");
	this->n = n;
	last = val.size() - 1;
	values = new T[n]; 
	
	size_t index = 0;
	for (auto i : val)
		values[index++] = i;
}

template <class T>
array<T>::array(const array<T>& arr)
{
	this->n = arr.getn();
	values = new T[n];
	
	for (auto i : arr)
		this->values[this->last++] = i;
	this->last--;
}

template <class T>
array<T>::array(const array<T>&& arr)
{
	this->n = arr.getn();
	values = new T[n];

	for (auto i : arr)
		this->values[this->last++] = i;
	this->last--;
}

//-----------------------------------------------------------------------------------
// actual functions:

template <class T>
void array<T>::shift_left(const size_t& left_position)
{
	if (empty())
		hard_error("nothing to shift");
	if(left_position)
		left_position--;
	for (size_t i = left_position; i < last; i++)
		values[i] = values[i + 1];
	values[last--] = NULL;
}


template <class T>
T& array<T>::operator [] (const size_t& index) const
{
	if (index > last)
		fatal_error("bad index");
	return values[index];
}

template <class T>
void array<T>::replce(const size_t& index, const T& value)
{
	if (index > n)
		fatal_error("bad index");
	if (index > last)
		values[++last] = value;
	else
		values[index] = value;
}

template <class T>
void array<T>::insert(const T& value)
{
	if (last + 1 == n)
		fatal_error("no more memory");
	values[++last] = value;
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
	for(size_t i = 0; i<= last;i++)
		if (values[i] == value)
		{
			shift_left(i + 1);
			if (all == false)
				return;
			i--;
		}
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


//-----------------------------------------------------------------------------------
// iterator:

template <class T>
iterator<T>::iterator(T* val)
{
	this->value = val;
}

template <class T>
T iterator<T>::operator*()
{
	return *value;
}

template <class T>
void iterator<T>::operator++()
{
	value++;
}

template <class T>
bool iterator<T>::operator != (const iterator& two)
{
	return (value != two.value);
}

template <class T>
iterator<T> array<T>::begin() const
{
	return iterator(&values[0]);
}

template <class T>
iterator<T> array<T>::end() const
{
	return iterator(&values[n]);
}

//-----------------------------------------------------------------------------------
// friend functions:

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
array<T> crossng(const array<T>& one, const array<T>& two)
{
	if (one.getn() <= two.getn())
	{
		array<T> new_array = one;

	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1		
	for (auto i : one);

	return new_array;
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
		sort_job->heaps(values, n, f);
		break;
	case quick_sort:
		sort_job->qucks(values, 0, last, f);
		break;
	default:
		break;
	}
}
