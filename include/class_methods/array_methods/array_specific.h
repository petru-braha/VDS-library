#pragma once
#include "../abstract class methods.h/specific_methods.h"

template <typename T>
class array_specific : specific_methods
{
	// typedefs:
	typedef const typename T& t;
	typedef const size_t& szt;

public:
	virtual void sort(bit algorithm) = 0;
	virtual typename array_specific<T>& insert(t value, szt index) = 0;
	virtual typename array_specific<T>& remove(szt index) = 0;
};
