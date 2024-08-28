#pragma once

template <class T>
class basic_iterator
{
public:
	virtual T		operator  * () const = 0;
	virtual void	operator ++ () = 0;
	virtual bool	operator != (const basic_iterator<T>& two) const = 0;
};
