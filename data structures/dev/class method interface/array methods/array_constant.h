#pragma once
#include "../abstract class methods/constant_methods.h"

template <class T, typename argument>
class array_constant : public constant_methods<argument>
{
	typedef const size_t& szt;

public:
	virtual T get(szt index) const = 0;
	virtual bool full() const = 0;
};
