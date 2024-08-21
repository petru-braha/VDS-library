#pragma once
#include "../abstract class methods.h/constant_methods.h"

template <class T>
class array_constant : constant_methods
{
	virtual T get(szt index) const = 0;
};