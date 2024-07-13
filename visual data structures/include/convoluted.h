#pragma once
#include <ostream>

class convoluted
{
	int number;
	bool& address1;
	char* address2;
public:
	// constructors:
	convoluted(const int& number, bool& one, const char*& two);
	convoluted(int null = NULL);
	~convoluted();
	
	// specific methods: 
	bool operator <  (const convoluted& c); // they only compare the first letter
	bool operator <= (const convoluted& c);
	bool operator >  (const convoluted& c);
	bool operator >= (const convoluted& c);
	bool operator == (const convoluted& c);
	bool operator != (const convoluted& c);
	
	// constant methods:
	int    get_numbr() const;
	bool&  get_addr1() const;
	void*  get_addr2() const;
	size_t get_bytes() const;

	// friend functions:
	friend std::ostream& operator << (std::ostream& out, const convoluted& c); // they assume: one > two
	friend bool compare_numbr(const convoluted& one, const convoluted& two);
	friend bool compare_addss(const convoluted& one, const convoluted& two);
	friend bool compare_strng(const convoluted& one, const convoluted& two);
};