#pragma once
#include "bureaucracy.h"
#include "array_sorting.h"
#include <initializer_list>

#define default_array_size 100

template <class T = int>
class array
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const size_t& szt;

	// data members:
	size_t n;			// its purpose is just to allocate space
	size_t index_last;	// gurantees that elements selected by user are initialised contiguously // index of the index_last concrete value
	T* values;

	// iterator concept:
	class iterator
	{
		T* value;
	public:
		iterator(T& val); // no const => avoid const cast

		T		operator  * () const;
		void	operator ++ ();
		bool	operator != (const iterator& two) const;
	};

	// auxiliar utility:
	fct  compare = [](type x, type y)->bool { return x > y; };
	void shift_left(szt left_position);

public:
	// constructors:
	~array();
	array(szt n = default_array_size);
	array(const std::initializer_list<T>& val, szt n = default_array_size);
	array(const T* val, szt val_size, szt n = default_array_size);
	array(const array<T>& arr);
	array(const array<T>&& arr) noexcept;

	// modifier methods:
	array<T>& operator = (const array<T>& arr);
	array<T>& operator = (const array<T>&& arr);
	array<T>& clear();
	array<T>& set_f(fct f);

	// specific methods:
	void sort(bit algorithm = quick_sort);
	array<T>& insert(type value, szt index);
	array<T>& remove(szt index);

	// constant methods:
	bool   operator == (const array<T>& arr) const;
	size_t get_n() const;
	size_t get_l() const;
	void*  get_f() const;
	bool   empty() const;
	void   print() const;
	T get(szt index) const;

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// query operations:
	size_t search(type value) const;
	size_t minimum() const;
	size_t maximum() const;
	size_t predcessr(szt index) const;
	size_t successor(szt index) const;
	T& operator [] (szt index); // get / replace method, shift to the left until there is no more empty space

	// instance synergy:
	array<T>& integrates(const array<T>& arr);
	array<T>& eliminates(const array<T>& arr);
	array<T>& intersects(const array<T>& arr);

	// friend functions:
	template <class T> friend T* convert(const array<T>& arr);
	template <class T> friend std::ostream& operator << (std::ostream& out, const array<T>& arr);
};

// comments:
// array[index_last] == the last value stored
// allows repeating values

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
	this->n = n;
	index_last = SZT_ERROR;
	values = new T[n]{}; // the initializer brachets will initialise everything with NULL
}

template <class T>
array<T>::array(const std::initializer_list<T>& val, szt n)
{
	if (val.size() > n)
		fatal_error("wrong parameters");
	this->n = n;
	index_last = val.size() - 1;
	values = new T[n]{};

	size_t index = 0;
	for (auto key = val.begin(); key != val.end(); key++)
	{
		values[index] = *key;
		index++;
	}
}

template <class T>
array<T>::array(const T* val, szt val_size, szt n)
{
	if (val_size > n)
		fatal_error("wrong parameters");
	this->n = n;
	values = new T[n]{};

	for (index_last = 0; index_last < val_size; index_last++)
		values[index_last] = val[index_last];
	index_last--;
}

template <class T>
array<T>::array(const array<T>& arr)
{
	this->n = arr.get_n();
	this->index_last = SZT_ERROR;
	values = new T[n]{};

	size_t index = 0;
	for (auto i : arr)
		this->values[index++] = i;
}

template <class T>
array<T>::array(const array<T>&& arr) noexcept
{
	this->n = arr.get_n();
	this->index_last = SZT_ERROR;
	values = new T[n]{};

	size_t index = 0;
	for (auto i : arr)
		this->values[index] = i;
}

//------------------------------------------------
// iterator methods:

template <class T>
array<T>::iterator::iterator(T& val)
{
	this->value = &val;
}

template <class T>
T array<T>::iterator::operator * () const
{
	return *value;
}

template <class T>
void array<T>::iterator::operator ++ ()
{
	value++;
}

template <class T>
bool array<T>::iterator::operator != (const iterator& two) const
{
	return value != two.value;
}

template <class T>
typename array<T>::iterator array<T>::begin() const
{
	return iterator(values[0]);
}

template <class T>
typename array<T>::iterator array<T>::end() const
{
	return iterator(values[index_last + 1]);
}

//------------------------------------------------
// modifier methods:

template <class T>
array<T>& array<T>::operator = (const array<T>& arr)
{
	this->n = arr.n;
	this->index_last = SZT_ERROR;
	delete[]this->values;
	this->values = new T[n]{};
	for (auto i : arr)
		this->values[++this->index_last] = i;
	return *this;
}

template <class T>
array<T>& array<T>::operator = (const array<T>&& arr)
{
	this->n = arr.n;
	this->index_last = SZT_ERROR;
	delete[]this->values;
	this->values = new T[n]{};
	for (auto i : arr)
		this->values[++this->index_last] = i;
	return *this;
}

template <class T>
array<T>& array<T>::clear()
{
	FOR(index_last)
		values[i] = NULL;
	values[index_last + 1] = NULL;
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
array<T>& array<T>::insert(type value, szt index)
{
	if (index > index_last + 1 || index < 0)
		hard_error("bad index");

	if (index_last + 1 >= n)
		fatal_error("no more memory");

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
	if (index <= index_last)
		shift_left(index);
	return *this;
}

//------------------------------------------------
// query operations:

template <class T>
size_t array<T>::search(type value) const
{
	FOR(index_last + 1)
		if (values[i] == value)
			return i;
	return SZT_ERROR;
}

template <class T>
size_t array<T>::minimum() const
{
	if (this->empty())
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
	if (this->empty())
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
	if (this->empty())
		hard_error("no data");
	if (index > index_last)
		hard_error("wrong parameters");

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
	if (this->empty())
		hard_error("no data");
	if (index > index_last)
		hard_error("wrong parameters");

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
	if (index >= n)
		hard_error("bad index");
	if (index > index_last + 1)
		hard_error("unallocated space"); // the user has to use insert, for adding a new value, not this operator
	if (index == index_last + 1)
	{
		index_last++;
		return values[index];
	}

	return values[index];
};

//------------------------------------------------
// constant methods:

template <class T>
bool array<T>::operator == (const array<T>& arr) const
{
	if (this->n != arr.n)
		return false;
	if (this->index_last != arr.index_last)
		return false;
	FOR(index_last + 1)
		if (values[i] != arr[i])
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
	return (void*)this->compare;
}


template <class T>
void  array<T>::print() const
{
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
	if (index > index_last)
		hard_error("bad index");
	return values[index];
}

//------------------------------------------------
// instance synergy:

template <class T>
array<T>& array<T>::integrates(const array<T>& arr);

template <class T>
array<T>& array<T>::eliminates(const array<T>& arr);

template <class T>
array<T>& array<T>::intersects(const array<T>& arr);

/*template <class T>
array<T> linking(const array<T>& one, const array<T>& two)
{
	if (one.get_n() > SZT_ERROR / 2 && two.get_n() > SZT_ERROR / 2)
		hard_error("no more memory");
	size_t new_n = one.get_n() + two.get_n();
	array<T> new_array(new_n);

	size_t index = 0;
	for (auto value : one)
	{
		new_array.insert(value, index);
		index++;
	}

	for (auto value : two)
	{
		new_array.insert(value, index);
		index++;
	}

	return new_array;
}

template <class T>
array<T> ejectin(const array<T>& one, const array<T>& two)
{
	array<T> new_array(one);
	for (auto value : two)
		FOR(new_array.get_l() + 1)
		if (new_array.get(i) == value)
			new_array.remove(i);
	return new_array;
}

template <class T>
array<T> crossng(const array<T>& one, const array<T>& two) // O(n*m), n = |one|, m = |two|. can be done in O(n + m) with a hash table
{
	array<T> new_array(one.get_n() + two.get_n());
	size_t index = 0;
	if (one.get_l() < two.get_l())
	{
		for (auto key : two)
			if (one.search(key) != SZT_ERROR)
			{
				new_array.insert(key, index);
				index++;
			}
	}
	else
	{
		for (auto key : one)
		{
			if (two.search(key) != SZT_ERROR)
			{
				new_array.insert(key, index);
				index++;
			}
		}
	}

	return new_array;
}
*/

//------------------------------------------------
// friend functions:

template <class T>
T* convert(const array<T>& arr)
{
	T* ptr = new T[arr.index_last + 1];
	FOR(arr.index_last + 1)
		ptr[i] = arr[i];
	return ptr;
}

template <class T>
std::ostream& operator << (std::ostream& out, const array<T>& arr)
{
	for (auto i : arr)
		out << i << ' ';
	out << '\n';
	return out;
}