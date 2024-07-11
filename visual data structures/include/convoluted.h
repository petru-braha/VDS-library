#pragma once
#include <ostream>

class convoluted
{
	int number;
	bool& address1;
	void* address2;
public:
	// constructors:
	convoluted(int number, bool& one, void* two);
	~convoluted();
	
	// specific methods: 
	bool operator <  (const convoluted& c);
	bool operator <= (const convoluted& c);
	bool operator >  (const convoluted& c);
	bool operator >= (const convoluted& c);
	bool operator == (const convoluted& c);
	bool operator != (const convoluted& c);
	
	// constant methods:
	int    get_numbr() const;
	int    get_addr1() const;
	int    get_addr2() const;
	size_t get_bytes() const;

	// friend functions:
	friend std::ostream& operator << (std::ostream& out, const convoluted& c);
	bool compare_numbr(const convoluted& one, const convoluted& two);
	bool compare_addss(const convoluted& one, const convoluted& two);
	bool compare_bytes(const convoluted& one, const convoluted& two);
};