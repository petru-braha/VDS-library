#pragma once

class modifier_methods {};
class specific_methods {};
class constant_methods {};
class query_operations {};
class instance_synergy {};
class iterator_methods {};

template <class T>
class array_specific
{
	// typedefs:
	typedef const T& type;
	typedef const size_t& szt;

public:
	virtual array_specific<T>& insert(type value, szt index) = 0;
	virtual array_specific<T>& remove(szt index) = 0;
};

template <typename T>
class data_structure : public T {};

template <class T>
class array : public data_structure<T> {};

