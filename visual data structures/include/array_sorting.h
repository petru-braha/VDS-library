#pragma once

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
class array_sorting // behavioral singleton
{
	typedef const T& type;
	typedef const size_t& szt;
	
	// one and two are considered arrays in the merge method
	void   merge(T*& arr, size_t one_index_left, size_t one_index_rght, size_t two_index_left, size_t two_index_rght);
	void   heapify(T*& arr, szt n, szt index, bool (*f)(type, type));
	size_t partition(T*& arr, szt left, szt rght, bool (*f)(type, type));

	static array_sorting<T>* instance;
	array_sorting() = default;
public:
	static array_sorting<T>* get_instance();

	void bubbs(T*& arr, szt n, bool (*f)(type, type) = nullptr);
	void seles(T*& arr, szt n, bool (*f)(type, type) = nullptr);
	void insrs(T*& arr, szt n, bool (*f)(type, type) = nullptr);

	void mrges(T*& arr, szt left, szt rght, bool (*f)(type, type) = nullptr);
	void heaps(T*& arr, szt n, bool (*f)(type, type) = nullptr);
	void qucks(T*& arr, szt left, szt rght, bool (*f)(type, type) = nullptr); 
};

template <class T>
array_sorting<T>* array_sorting<T>::instance = nullptr;
