#pragma once

template <class T, typename argument>
class modifier_methods 
{
	typedef const T& t;
	typedef bool (*fct)(t, t);

public:
	virtual modifier_methods& operator = (const argument& structure) = 0;
	virtual modifier_methods& clear() = 0;
	virtual modifier_methods& set_f(fct f) = 0;
};

// comments:
// the first typename
// DOES NOT have to be derivated
