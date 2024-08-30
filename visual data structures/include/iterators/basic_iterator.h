#pragma once

template <class T, typename argument>
class basic_iterator
{
public:
	virtual T		operator  * () const = 0;
	virtual void	operator ++ () = 0;
	virtual bool	operator != (const argument& two) const = 0;
};
