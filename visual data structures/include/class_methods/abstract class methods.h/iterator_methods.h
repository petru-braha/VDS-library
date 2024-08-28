#pragma once

template <typename iterator_object>
class iterator_methods
{
public:
	virtual iterator_object begin() const = 0;
	virtual iterator_object end() const = 0;
};
