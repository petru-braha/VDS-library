#pragma once
#include "../abstract class methods/specific_methods.h"

template <class T>
class array_specific : public specific_methods
{
	typedef const T& t;
	typedef const size_t& szt;

public:
	virtual array_specific& sort(bit algorithm) = 0;
	virtual array_specific& insert(t value, szt index) = 0;
	virtual array_specific& remove(szt index) = 0;
};
