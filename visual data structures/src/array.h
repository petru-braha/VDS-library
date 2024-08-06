#pragma once
#pragma warning (once:4018)
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

	// data members:
	size_t n;			// its purpose is just to allocate space
	loong index_last;	// gurantees that elements selected by user are initialised contiguously // index of the index_last concrete value
	T* values;

	// iterator concept:
	class iterator
	{
		T* value;
	public:
		iterator(T& val);

		T		operator  * () const;
		void	operator ++ ();
		bool	operator != (const iterator& two) const;
	};

	// auxiliar utility:
	fct  compare = [](type x, type y)->bool { return x > y; };
	void shift_left(const size_t& left_position);
public:
	// constructors:
	~array();
	array(const size_t& n = default_array_size);
	array(const std::initializer_list<T>& val, const size_t& n = default_array_size);
	array(const T* val, const size_t& val_size, const size_t& n = default_array_size);
	array(const array<T>& arr);
	array(const array<T>&& arr) noexcept;

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// modifier methods:
	array<T>& operator = (const array<T>& arr);
	void clear();
	void setf(fct f);

	// specific methods:
	void sort(const bit& algorithm = quick_sort);
	void insert(const T& value, const size_t& index);
	void remove(const size_t& index);
	void remove(const T& value, const bool& all);

	// query operations:
	size_t search(const T& value) const;
	size_t minimum() const;
	size_t maximum() const;
	size_t predcessr(const T& value) const;
	size_t successor(const T& value) const;
	T& operator [] (const size_t& index); // get / replace method, shift to the left until there is no more empty space

	// constant methods:
	bool operator == (const array<T>& arr) const;
	size_t getn() const;
	loong  getl() const;
	void*  getf() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions:
	friend T* convert(const array<T>& arr);

	template <class T> friend array<T> linking(const array<T>& one, const array<T>& two);
	template <class T> friend array<T> ejectin(const array<T>& one, const array<T>& two);
	template <class T> friend array<T> crossng(const array<T>& one, const array<T>& two);

	friend std::ostream& operator << (std::ostream& out, const array<T>& arr);
};

// comments:
// array[index_last] == the last value stored
// allows repeating values

//------------------------------------------------
// auxiliar utility:

template <class T>
void array<T>::shift_left(const size_t& left_position)
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
array<T>::array(const size_t& n)
{
	this->n = n;
	index_last = ERROR_CODE;
	values = new T[n];
	for (size_t i = 0; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const std::initializer_list<T>& val, const size_t& n)
{
	if (val.size() > n)
		fatal_error("wrong parameters");
	this->n = n;
	index_last = val.size() - 1;
	values = new T[n];

	size_t index = 0;
	for (auto key = val.begin(); key != val.end(); key++)
	{
		values[index] = *key;
		index++;
	}

	for (; index < n; index++)
		values[index] = NULL;
}

template <class T>
array<T>::array(const T* val, const size_t& val_size, const size_t& n)
{
	if (val_size > n)
		fatal_error("wrong parameters");
	this->n = n;
	values = new T[n];

	for (index_last = 0; index_last < val_size; index_last++)
		values[index_last] = val[index_last];
	index_last--;

	for (size_t i = index_last + 1; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const array<T>& arr)
{
	this->n = arr.getn();
	this->index_last = ERROR_CODE;
	values = new T[n];

	for (auto i : arr)
		this->values[++this->index_last] = i;
	for (size_t i = index_last + 1; i < n; i++)
		values[i] = NULL;
}

template <class T>
array<T>::array(const array<T>&& arr) noexcept
{
	this->n = arr.getn();
	this->index_last = ERROR_CODE;
	values = new T[n];

	for (auto i : arr)
		this->values[++this->index_last] = i;
	for (size_t i = index_last + 1; i < n; i++)
		values[i] = NULL;
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
	this->index_last = ERROR_CODE;
	delete[]this->values;
	this->values = new T[n];
	for (auto i : arr)
		this->values[++this->index_last] = i;
	return *this;
}

template <class T>
void array<T>::clear()
{
	FOR(index_last + 1)
		values[i] = NULL;
	index_last = ERROR_CODE;
}

template <class T>
void array<T>::setf(fct f)
{
	this->compare = f;
}

//------------------------------------------------
// specific methods:

template <class T>
void array<T>::sort(const bit& algorithm)
{
	array_sorting<T>* sort_job = array_sorting<T>::get_instance();
	sort_job->setf(this->compare);

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
void array<T>::insert(const T& value, const size_t& index)
{
	if (index > index_last + 1 || index < 0)
		hard_error("bad index");

	if (index_last + 1 >= n)
		fatal_error("no more memory")

		index_last++;
	for (size_t i = index_last; i > index; i--) // shift right
		values[i] = values[i - 1];
	values[index] = value;
}

template <class T>
void array<T>::remove(const size_t& index)
{
	if (empty())
		return;
	if (index >= n)
		hard_error("bad index");
	if (index <= index_last)
		shift_left(index);
}

template <class T>
void array<T>::remove(const T& value, const bool& all)
{
	for (size_t i = 0; i <= index_last; i++)
		if (values[i] == value)
		{
			shift_left(i);
			if (all == false)
				return;
			i--;
		}
}

//------------------------------------------------
// query operations:

template <class T>
size_t array<T>::search(const T& value) const
{
	FOR(index_last + 1)
		if (values[i] == value)
			return i;
	return ERROR_CODE;
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
size_t array<T>::predcessr(const T& value) const
{
	if (this->empty())
		hard_error("no data");

	size_t index_predecessor = ERROR_CODE;
	FOR(index_last + 1)
		if (compare(value, values[i]))
		{
			if (index_predecessor == ERROR_CODE)
				index_predecessor = i;
			else if (compare(values[i], values[index_predecessor]))
				index_predecessor = i;
		}

	return index_predecessor;
}

template <class T>
size_t array<T>::successor(const T& value) const
{
	if (this->empty())
		hard_error("no data");

	size_t index_successor = ERROR_CODE;
	FOR(index_last + 1)
		if (compare(values[i], value))
		{
			if (index_successor == ERROR_CODE)
				index_successor = i;
			else if (compare(values[index_successor], values[i]))
				index_successor = i;
		}

	return index_successor;
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
	FOR(index_last + 1)
		if (values[i] != arr[i])
			return false;
	return true;
}

template <class T>
T& array<T>::operator [] (const size_t& index)
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

template <class T>
size_t array<T>::getn() const
{
	return n;
}

template <class T>
loong array<T>::getl() const
{
	return index_last;
}

template <class T>
void* array<T>::getf() const
{
	return (void*)this->compare;
}


template <class T>
void  array<T>::prnt() const
{
	FOR(index_last + 1)
		std::cout << values[i] << ' ';
	std::cout << '\n';
}

template <class T>
bool array<T>::empty() const
{
	return index_last == ERROR_CODE;
}

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
array<T> linking(const array<T>& one, const array<T>& two)
{
	size_t new_n = one.getn() + two.getn();
	array<T> new_array(new_n);
	for (auto value : one)
		new_array.insert(value, new_array.getl() + 1);
	for (auto value : two)
		new_array.insert(value, new_array.getl() + 1);
	return new_array;
}

template <class T>
array<T> ejectin(const array<T>& one, const array<T>& two)
{
	array<T> new_array(one);
	for (auto value : two)
		new_array.remove(value, true);
	return new_array;
}

template <class T>
array<T> crossng(const array<T>& one, const array<T>& two) // O(n*m), n = |one|, m = |two|. can be done in O(n + m) with a hash table
{
	array<T> new_array(one.getn() + two.getn());
	if (one.getl() < two.getl())
	{
		for (auto key : two)
			if (one.search(key) != ERROR_CODE)
				new_array.insert(key, new_array.getl() + 1);
	}
	else
	{
		for (auto key : one)
		{
			if (two.search(key) != ERROR_CODE)
				new_array.insert(key, new_array.getl() + 1);
		}
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
