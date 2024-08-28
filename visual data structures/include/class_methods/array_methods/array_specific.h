#pragma once
#include "../abstract class methods.h/specific_methods.h"

template <class T>
class array_specific : public specific_methods
{
	// typedefs:
	typedef const T& t;
	typedef const size_t& szt;

public:
	virtual void sort(bit algorithm) = 0;
	virtual array_specific<T>& insert(t value, szt index) = 0;
	virtual array_specific<T>& remove(szt index) = 0;
};
