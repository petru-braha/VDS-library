#pragma once

class modifier_methods 
{
public:
	typedef const modifier_methods& m_type;

	virtual modifier_methods& operator = (m_type structure) = 0;
	virtual modifier_methods& clear() = 0;
	virtual modifier_methods& set_f(void* f) = 0;
};

// comments:
// the first typename
// DOES NOT have to be derivated
