#pragma once
#include "array.h"

enum
{
	bubble_sort,
	selection_sort,
	insertion_sort,

	merge_sort,
	heap_sort,
	quick_sort
};

template <class T = int>
class array_sorting // singleton
{
	static array_sorting<T>* instance;
	array<T>* arr;
	array_sorting(array<T>* arr);
public:
	static array_sorting<T>* get_instance(array<T>* arr);

	void bubbs();
	void seles();
	void insrs();

	void mrges();
	void heaps();
	void qucks();
	
	~array_sorting();
};

template <class T = int>
array_sorting<T>::instance = nullptr;