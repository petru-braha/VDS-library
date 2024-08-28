#pragma once
#include "bureaucracy.h"

enum sorting_algoritms
{
	bubble_sort,
	selection_sort,
	insertion_sort,

	merge_sort,
	heap_sort,
	quick_sort
};

template <class T = int>
class array_sorting // behavioral singleton
{
	structure_typedefs;

	// auxiliar utility:
	fct  compare = [](t x, t y)->bool { return x > y; };

	void   swap(T*& arr, szt one, szt two); // one, two == arrays 
	void   merge(T*& arr, size_t one_index_left, size_t one_index_rght, size_t two_index_left, size_t two_index_rght);
	void   heapify(T*& arr, szt n, szt index);

	// for quick_sort:
	T      median_three(t one, t two, t three);
	size_t partition(T*& arr, szt left, szt rght);

	// constructors:
	static array_sorting<T>* instance;
	array_sorting() = default;

public:
	static array_sorting<T>* get_instance();

	// specific methods:
	void set_f(fct f);
	void bubbs(T*& arr, szt n);
	void seles(T*& arr, szt n);
	void insrs(T*& arr, szt n);

	void mrges(T*& arr, szt left, szt rght);
	void heaps(T*& arr, szt n);
	void qucks(T*& arr, szt left, szt rght);
};


//------------------------------------------------
// auxiliar utility:

template <class T>
void array_sorting<T>::swap(T*& arr, szt one, szt two)
{
	T temp = arr[one];
	arr[one] = arr[two];
	arr[two] = temp;
}

//------------------------------------------------
// constructors:

template <class T>
array_sorting<T>* array_sorting<T>::instance = nullptr;

template <class T>
array_sorting<T>* array_sorting<T>::get_instance()
{
	if (instance == nullptr)
		instance = new array_sorting<T>();
	return instance;
}

//------------------------------------------------
// specific methods:

template <class T>
void array_sorting<T>::set_f(fct f)
{
	this->compare = f;
}

template <class T>
void array_sorting<T>::bubbs(T*& arr, szt n)
{
	bool sorted = false;
	do
	{
		sorted = true;
		for (size_t index = 1; index < n; index++)
			if (compare(arr[index - 1], arr[index]))
			{
				sorted = false;
				swap(arr, index - 1, index);
			}
	} while (sorted == false);
}

template <class T>
void array_sorting<T>::seles(T*& arr, szt n)
{
	for (size_t i = 0; i < n - 1; i++)
	{
		size_t index_minimum = i;
		for (size_t j = i + 1; j < n; j++)
			if (compare(arr[index_minimum], arr[j]))
				index_minimum = j;

		if (index_minimum != i)
			swap(arr, index_minimum, i);
	}
}

template <class T>
void array_sorting<T>::insrs(T*& arr, szt n)
{
	T key = 0;
	for (size_t i = 1; i < n; i++)
	{
		key = arr[i];
		size_t j = NULL;
		for (j = i - 1; compare(arr[j], key); j--)
		{
			arr[j + 1] = arr[j];
			if (j == 0) { arr[j] = key; break; }
		}

		if (j) arr[j + 1] = key;
	}
}
//------------------------------------------------
// merge_sort:

template <class T>
void array_sorting<T>::merge(T*& arr, size_t one_index_left, size_t one_index_rght, size_t two_index_left, size_t two_index_rght)
{
	size_t index_temp = 0, n_temp = two_index_rght - one_index_left;
	T* temp_array = new T[n_temp];
	FOR(n_temp)
		temp_array[i] = NULL;

	while (one_index_left < one_index_rght && two_index_left < two_index_rght)
	{
		if (compare(arr[one_index_left], arr[two_index_left]))
		{
			temp_array[index_temp++] = arr[two_index_left];
			two_index_left++;
		}
		else
		{
			temp_array[index_temp++] = arr[one_index_left];
			one_index_left++;
		}
	}

	for (; one_index_left < one_index_rght; one_index_left++)
		temp_array[index_temp++] = arr[one_index_left];
	for (; two_index_left < two_index_rght; two_index_left++)
		temp_array[index_temp++] = arr[two_index_left];
	for (size_t i = 0; i < n_temp; i++)
		arr[i + one_index_left] = temp_array[i];
	delete[]temp_array;
}

template <class T>
void array_sorting<T>::mrges(T*& arr, szt left, szt rght)
{
	if (left >= rght)
		return;
	size_t index_middle = left + (rght - left) / 2;
	mrges(arr, left, index_middle);
	mrges(arr, index_middle + 1, rght);
	merge(arr, left, index_middle + 1, index_middle + 1, rght + 1);
}

//------------------------------------------------
// heap_sort: 

template <class T>
void array_sorting<T>::heapify(T*& arr, szt n, szt index)
{
	size_t index_largest = index, index_left = index * 2 + 1, index_rght = index * 2 + 2;

	if (compare(arr[index_left], arr[index_largest]) && index_left < n)
		index_largest = index_left;
	if (compare(arr[index_rght], arr[index_largest]) && index_rght < n)
		index_largest = index_rght;

	if (index != index_largest)
	{
		swap(arr, index, index_largest);
		heapify(arr, n, index_largest);
	}
}

template <class T>
void array_sorting<T>::heaps(T*& arr, szt n)
{
	// build
	for (long long i = (long long)n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	//sort
	for (long long i = (long long)n - 1; i >= 0; i--)
	{
		swap(arr, 0, i);
		heapify(arr, i, 0);
	}
}

//------------------------------------------------
// quick_sort: 

template <class T>
T array_sorting<T>::median_three(t one, t two, t three)
{
	if (compare(one, two))
	{
		if (compare(three, one))
			return one;
		if (compare(three, two))
			return three;
		return two;
	}
	else
	{
		if (compare(one, three))
			return one;
		if (compare(two, three))
			return three;
		return two;
	}
}

template <class T>
size_t array_sorting<T>::partition(T*& arr, szt left, szt rght)
{
	T one = arr[left], two = arr[left + (rght - left) / 2], three = arr[rght];
	T pivot = median_three(one, two, three);

	size_t i = left - 1, j = rght + 1;
	while (true)
	{
		do { i++; } while (compare(pivot, arr[i]));
		do { j--; } while (compare(arr[j], pivot));

		if (i >= j)
			return j;
		swap(arr, i, j);
	}
}

template <class T>
void array_sorting<T>::qucks(T*& arr, szt left, szt rght)
{
	if (left >= rght)
		return;
	size_t p = partition(arr, left, rght);
	qucks(arr, left, p);
	qucks(arr, p + 1, rght);
}
