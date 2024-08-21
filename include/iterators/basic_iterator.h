#pragma once

template <class T>
class basic_iterator
{
public:
	T		operator  * () const = 0;
	void	operator ++ () = 0;
	bool	operator != (const iterator& two) const = 0;
};
