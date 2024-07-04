#include "pch.h"
#include "../include/array.h"

template <class T>
void array<T>::sort(const int& algorithm)
{
	array_sorting sort_job(this);
	switch (algorithm)
	{
	case bubble_sort:
		
		break;
	case selection_sort:
		break;
	case insertion_sort:
		break;
	case merge_sort:
		break;
	case heap_sort:
		break;
	case quick_sort:
		break;
	default:
		break;
	}
}
