#pragma once
#include "bureaucracy.h"

#include "class_methods/abstract class methods.h/modifier_methods.h"
#include "class_methods/array_methods/array_specific.h"
#include "class_methods/array_methods/array_constant.h"
#include "class_methods/array_methods/array_queries.h"
#include "class_methods/abstract class methods.h/instance_synergy.h"
#include "class_methods/abstract class methods.h/iterator_methods.h"

#include "iterators/array_iterator.h"

#include "array_sorting.h"
#include "data_structure.h"
#include <initializer_list>

/* comments:
	- values[0 ... index_last] == 'set values'
	- values[index_last + 1 ... n - 1] == 'non-set values'
	- array[index_last] == the last value stored
	- allows repeating values
*/

template <class T = int>
class array : public data_structure<modifier_methods<T, array<T>>, array_specific<T>, 
	array_constant<T, array<T>>, array_queries<T>, 
	instance_synergy<array<T>>, iterator_methods<array_iterator<T>>>
{
	// typedefs:
	structure_typedefs;

public:
	// constructors:
	~array();
	array(szt n = default_array_size);
	array(const std::initializer_list<T>& data, szt n = default_array_size);
	array(const T* data, szt data_n, szt n = default_array_size);
	array(const array<T>& arr);
	array(const array<T>&& arr) noexcept;

	// modifier methods:
	array<T>& operator = (const array<T>& arr);
	array<T>& clear();
	array<T>& set_f(fct f);

	// specific methods:
	void sort(bit algorithm = quick_sort);
	array<T>& insert(t value, szt index);
	array<T>& remove(szt index);

	// constant methods:
	bool   operator == (const array<T>& arr) const;
	size_t get_n() const;
	size_t get_l() const;
	void*  get_f() const;
	bool   empty() const;
	void   print() const;
	T get(szt index) const;
	bool full() const;

	// query operations:
	size_t search(t value) const;
	size_t minimum() const;
	size_t maximum() const;
	size_t predcessr(szt index) const;
	size_t successor(szt index) const;
	T& operator [] (szt index); // get / replace method, shift to the left until there is no more empty space

	// instance synergy:
	array<T>& integrates(const array<T>& arr);
	array<T>& eliminates(const array<T>& arr);
	array<T>& intersects(const array<T>& arr);

	// iterator methods:
	array_iterator<T> begin() const;
	array_iterator<T> end() const;

	// friend functions:
	template <class T> friend T* convert(const array<T>& arr);
	template <class T> friend std::ostream& operator << (std::ostream& out, const array<T>& arr);

private:
	// data members:
	size_t n;			// its purpose is just to allocate space
	size_t index_last;	// gurantees that elements selected by user are initialised contiguously // index of the index_last concrete value
	T* values;

	// auxiliar utility:
	fct  compare;
	void shift_left(szt left_position);

public:	
	static const size_t default_array_size;
};

//------------------------------------------------
// constructors:

template <class T>
array<T>::~array()
{
	delete[]values;
}

template <class T>
array<T>::array(szt n)
{
	if (n * sizeof(T) > INT_MAX)
		fatal_error("too much data on stack");
	if (n == 0)
		fatal_error("size of the array can not be 0");
	
	this->n = n;
	index_last = SZT_ERROR;
	values = new T[n]{};

	compare = [](t x, t y)->bool { return x > y; };
}

template <class T>
array<T>::array(const std::initializer_list<T>& data, szt n) : array<T>(n)
{
	if (data.size() > n)
	{
		delete[]values;
		fatal_error("wrong parameters");
	}

	for (auto key : data)
	{
		index_last++;
		values[index_last] = key;
	}
}

template <class T>
array<T>::array(const T* data, szt data_n, szt n) : array<T>(n)
{
	if (data_n > n)
	{
		delete[]values;
		fatal_error("wrong parameters");
	}
	
	for (index_last = 0; index_last < data_n; index_last++)
		values[index_last] = data[index_last];
	index_last--;
}

template <class T>
array<T>::array(const array<T>& arr) : array<T>(arr.n)
{
	for (auto i : arr)
	{
		index_last++;
		this->values[index_last] = i;
	}
}

template <class T>
array<T>::array(const array<T>&& arr) noexcept : array<T>(arr.n)
{
	for (auto i : arr)
	{
		index_last++;
		this->values[index_last] = i;
	}
}

//------------------------------------------------
// modifier methods:

template <class T>
array<T>& array<T>::operator = (const array<T>& arr)
{
	this->n = arr.n;
	this->index_last = arr.index_last;
	delete[]this->values;
	this->values = new T[arr.n]{};
	
	
	for (size_t index = 0; index < arr.n; index++)
	{
		this->values[index] = arr.get(index);
		index++;
	}

	this->compare = arr.compare;
	return *this;
}

template <class T>
array<T>& array<T>::clear()
{
	if (empty())
		return *this;

	FOR(index_last)
		values[i] = NULL;
	values[index_last] = NULL;
	index_last = SZT_ERROR;
	return *this;
}

template <class T>
array<T>& array<T>::set_f(fct f)
{
	this->compare = f;
	return *this;
}

//------------------------------------------------
// specific methods:

template <class T>
void array<T>::sort(bit algorithm)
{
	array_sorting<T>* sort_job = array_sorting<T>::get_instance();
	sort_job->set_f(this->compare);

	switch (algorithm)
	{
	case bubble_sort:
		sort_job->bubbs(values, index_last + 1);
		break;
	case selection_sort:
		sort_job->seles(values, index_last + 1);
		break;
	case insertion_sort:
		sort_job->insrs(values, index_last + 1);
		break;
	case merge_sort:
		sort_job->mrges(values, 0, index_last);
		break;
	case heap_sort:
		sort_job->heaps(values, index_last + 1);
		break;
	case quick_sort:
		sort_job->qucks(values, 0, index_last);
		break;
	default:
		break;
	}
}

template <class T>
array<T>& array<T>::insert(t value, szt index)
{
	if (empty())
	{
		values[0] = value;
		index_last++;
		return *this;
	}

	if (full())
	{
		delete[]values;
		fatal_error("no more memory");
	}
	
	if (index > index_last + 1)
		hard_error("bad index");
	
	index_last++;
	for (size_t i = index_last; i > index; i--) // shift right
		values[i] = values[i - 1];
	values[index] = value;
	return *this;
}

template <class T>
array<T>& array<T>::remove(szt index)
{
	if (empty())
		return *this;

	if (index >= n)
		hard_error("bad index");
	// no punishment for indexing a non-set value?
	if (index <= index_last)
		shift_left(index);
	return *this;
}

//------------------------------------------------
// constant methods:

template <class T>
bool array<T>::operator == (const array<T>& arr) const
{
	if (this->n != arr.n)
		return false;
	if (this->index_last != arr.index_last)
		return false;

	if (this->empty() && arr.empty())
		return true;

	FOR(index_last + 1)
		if (values[i] != arr.get(i))
			return false;
	return true;
}

template <class T>
size_t array<T>::get_n() const
{
	return n;
}

template <class T>
size_t array<T>::get_l() const
{
	if (empty())
		hard_error("no data");
	return index_last;
}

template <class T>
void* array<T>::get_f() const
{
	return (void*)compare;
}


template <class T>
void array<T>::print() const
{
	if (empty())
		return;

	FOR(index_last + 1)
		std::cout << values[i] << ' ';
	std::cout << '\n';
}

template <class T>
bool array<T>::empty() const
{
	return (values[0] == NULL && SZT_ERROR == index_last);
}

template <class T>
T array<T>::get(szt index) const
{
	if (empty())
		hard_error("no data");

	if (index > index_last)
		hard_error("bad index");
	return values[index];
}

template <class T>
bool array<T>::full() const
{
	return index_last + 1 == n;
}

//------------------------------------------------
// query operations:

template <class T>
size_t array<T>::search(t value) const
{
	if (empty())
		hard_error("no data");
	
	FOR(index_last + 1)
		if (values[i] == value)
			return i;
	return SZT_ERROR;
}

template <class T>
size_t array<T>::minimum() const
{
	if (empty())
		hard_error("no data");

	size_t index_minimum = NULL;
	FOR(index_last + 1)
		if (compare(values[index_minimum], values[i]))
			index_minimum = i;
	return index_minimum;
}

template <class T>
size_t array<T>::maximum() const
{
	if (empty())
		hard_error("no data");

	size_t index_maximum = NULL;
	FOR(index_last + 1)
		if (compare(values[i], values[index_maximum]))
			index_maximum = i;
	return index_maximum;
}

template <class T>
size_t array<T>::predcessr(szt index) const
{
	if (empty())
		hard_error("no data");
	if (index > index_last)
		hard_error("bad index");

	size_t index_predecessor = SZT_ERROR;
	FOR(index_last + 1)
		if (compare(values[index], values[i]))
		{
			if (index_predecessor == SZT_ERROR)
				index_predecessor = i;
			else if (compare(values[i], values[index_predecessor]))
				index_predecessor = i;
		}

	return index_predecessor;
}

template <class T>
size_t array<T>::successor(szt index) const
{
	if (empty())
		hard_error("no data");
	if (index > index_last)
		hard_error("bad index");

	size_t index_successor = SZT_ERROR;
	FOR(index_last + 1)
		if (compare(values[i], values[index]))
		{
			if (index_successor == SZT_ERROR)
				index_successor = i;
			else if (compare(values[index_successor], values[i]))
				index_successor = i;
		}

	return index_successor;
}

template <class T>
T& array<T>::operator [] (szt index)
{
	if (empty())
		hard_error("no data");
	if (index >= n)
		hard_error("bad index");
	if (index > index_last)
		hard_error("non-set value, use insert method"); // the user has to use insert, for adding a new value, not this operator
	
	return values[index];
};

//------------------------------------------------
// instance synergy:

template <class T>
array<T>& array<T>::integrates(const array<T>& arr)
{
	if ((this->n + arr.n) * sizeof(T) > INT_MAX)
		hard_error("too much data on stack");
	
	this->n += arr.n;
	T* new_values = new T[this->n]{};
	
	size_t index = 0;
	FOR(this->index_last + 1)
	{
		new_values[index] = this->values[i];
		index++;
	}
	
	FOR(arr.index_last + 1)
	{
		new_values[index] = arr.get(i);
		index++;
	}

	delete[]this->values;
	this->index_last += (arr.index_last + 1);
	this->values = new_values;
	return *this;
}

template <class T>
array<T>& array<T>::eliminates(const array<T>& arr)
{
	if (this->empty())
		return *this;

	for (auto value : arr)
		FOR(this->get_l() + 1)
		if (this->get(i) == value)
			this->remove(i);
	return *this;
}

template <class T>
array<T>& array<T>::intersects(const array<T>& arr) // O(n*m), n = |one|, m = |two|. can be done in O(n + m) with a hash table
{
	size_t index = 0;
	size_t new_n = this->n > arr.n ? this->n : arr.n;
	T* new_values = new T[new_n]{};

	if (this->empty() || arr.empty())
	{
		this->clear();
		return *this;
	}

	if (this->get_l() < arr.get_l())
	{
		for (auto key : arr)
			if (this->search(key) != SZT_ERROR)
				new_values[index++] = key;
	}
	else
	{
		for (auto key : *this)
			if (arr.search(key) != SZT_ERROR)
				new_values[index++] = key;
	}

	delete[]this->values;
	this->values = new_values;
	this->index_last = index - 1;

	return *this;
}

//------------------------------------------------
// iterator methods:

template <class T>
array_iterator<T> array<T>::begin() const
{
	if (empty())
		hard_error("no data");
	return values[0];
}

template <class T>
array_iterator<T> array<T>::end() const
{
	if (empty())
		hard_error("no data"); 
	return values[index_last + 1];
}

//------------------------------------------------
// friend functions:

template <class T>
T* convert(const array<T>& arr)
{
	if (arr.empty())
		return nullptr;

	T* ptr = new T[arr.index_last + 1];
	FOR(arr.index_last + 1)
		ptr[i] = arr[i];
	return ptr;
}

template <class T>
std::ostream& operator << (std::ostream& out, const array<T>& arr)
{
	if (arr.empty())
		return out;

	for (auto i : arr)
		out << i << ' ';
	out << '\n';
	return out;
}

//------------------------------------------------
// auxiliar utility:

template <class T>
void array<T>::shift_left(szt left_position)
{
	if (empty())
		fatal_error("nothing to shift");

	for (size_t i = left_position; i < index_last; i++)
		values[i] = values[i + 1];
	values[index_last--] = NULL;
}

template <class T>
const size_t array<T>::default_array_size = 100;
