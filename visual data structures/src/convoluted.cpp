#include "convoluted.h"

convoluted::convoluted(int number, bool& one, void* two) : number(number), address1(one)
{
	address2 = (char*
}

convoluted::~convoluted()
{

}

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