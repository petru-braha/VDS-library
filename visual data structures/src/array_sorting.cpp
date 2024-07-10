#pragma once
#include "pch.h"
#include "../include/array_sorting.h"
#include "../include/bureaucracy.h"

template <class T>
void swap(T*& arr, const size_t& one, const size_t& two)
{
	T temp = arr[one];
	arr[one] = arr[two];
	arr[two] = temp;
}

template <class T>
array_sorting<T>* array_sorting<T>::get_instance()
{
	if (instance == nullptr)
		instance = new array_sorting<T>();
	return instance;
}

template <class T>
void array_sorting<T>::bubbs(T*& arr, szt n, bool (*f)(type, type))
{
	if (f == nullptr) f = [](type x, type y)->bool { return x > y; };
	bool sorted = false;
	do
	{
		sorted = true;
		for(size_t index = 1; index < n; index++)
			if (f( arr[index - 1], arr[index] ))
			{
				sorted = false;
				const T temp = arr[index - 1];
				arr[index - 1] = arr[index];
				arr[index] = temp;
			}
	} while (sorted == false);
}

//--------------------------------------------------------------------------------------
// heap sort: 

template <class T>
void array_sorting<T>::heapify(T*& arr, szt n, szt index, bool (*f)(type, type))
{
	size_t index_largest = index, index_left = index * 2 + 1, index_rght = index * 2 + 2;

	if (f(arr[index_left], arr[index_largest]) && index_left < n)
		index_largest = index_left;
	if (f(arr[index_rght], arr[index_largest]) && index_rght < n)
		index_largest = index_rght;

	if (index != index_largest)
	{
		swap(arr, index, index_largest);
		heapify(arr, n, index_largest, f);
	}
}

template <class T>
void array_sorting<T>::heaps(T*& arr, szt n, bool (*f)(type, type))
{
	// build
	if (f == nullptr) f = [](type x, type y)->bool {return x > y; };
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i, f);

	//sort
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr, 0, i);
		heapify(arr, i, 0, f);
	}
}

//--------------------------------------------------------------------------------------
// quick sort: 

template <class T>
T median_three(const T& one, const T& two, const T& three, bool (*f)(const T&, const T&))
{
	if (f(one, two))
	{
		if (f(three, one))
			return one;
		if (f(three, two))
			return three;
		return two;
	}
	else
	{
		if (f(one, three))
			return one;
		if (f(two, three))
			return three;
		return two;
	}

	hard_error("choosing median pivot failed");
}

template <class T>
size_t array_sorting<T>::partition(T*& arr, szt left, szt rght, bool (*f)(type, type))
{
	if (f == nullptr) f = [](type x, type y)->bool { return x > y; };

	T one = arr[left], two = arr[left + (rght - left) / 2], three = arr[rght];
	T pivot = median_three(one, two, three, f);

	size_t i = left - 1, j = rght + 1;
	while (true)
	{
		do { i++; } while (f(pivot, arr[i]));
		do { j--; } while (f(arr[j], pivot));

		if (i >= j)
			return j;
		swap(arr, i, j);
	}
}

template <class T>
void array_sorting<T>::qucks(T*& arr, szt left, szt rght, bool (*f)(type, type))
{
	if (left >= rght)
		return;
	size_t p = partition(arr, left, rght, f);
	qucks(arr, left, p);
	qucks(arr, p + 1, rght);
}
