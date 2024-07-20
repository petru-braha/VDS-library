#pragma once
#include <limits>

const std::initializer_list<int>    list_integer = { -1, 0, 1, SHRT_MAX, LONG_MAX, SHRT_MIN, LONG_MIN, -1, 1, LONG_MIN };
const std::initializer_list<char>   list_charact = { 0, 1, 0, CHAR_MAX, CHAR_MIN, 'A', 'a', -1, 0, 'a' };
const std::initializer_list<float>  list_numeral = { -1, 0.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };
const std::initializer_list<size_t> list_largenr = { 1, 0, 1, UCHAR_MAX, USHRT_MAX, ULLONG_MAX,LLONG_MAX, 1, 0, ULONG_MAX };
		
#define classic_size 10
#define maximum_size 15 // allowing for testing to insert five more elements
const int    block_integer[maximum_size] = { -1, 0, 1, SHRT_MAX, LONG_MAX, SHRT_MIN, LONG_MIN, -1, 1, LONG_MIN };
const char   block_charact[maximum_size] = { 0, 1, 0, CHAR_MAX, CHAR_MIN, 'A', 'a', -1, 0, 'a' };
const float  block_numeral[maximum_size] = { -1, 0.01f, +1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };
const size_t block_largenr[maximum_size] = { 1, 0, 1, UCHAR_MAX, USHRT_MAX, ULLONG_MAX,LLONG_MAX, 1, 0, ULONG_MAX };

const convoluted obj0 = { 5, true, "letters" };
const convoluted obj1 = { 5, false, "letters" };
const convoluted obj2 = { 4, true, "letters" };
const convoluted obj3 = { 4, false, "letters" };
const convoluted obj4 = { 5, true, "ladders_zzz" };
const convoluted obj5 = { 5, false, "ladders_zzz" };
const convoluted obj6 = NULL;
const convoluted obj7 = { 1, true, "z" };
const convoluted obj8 = { 1, true, "a" };
const convoluted obj9 = { 1, false, "a" };

const std::initializer_list<const convoluted> list_objects = { obj0, obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9 };
const convoluted block_objects[maximum_size] = { obj0, obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9 };

// sorted using comparing method:
// - the following numbers represent the index of objects of type convoluted;
// 1. number - int		(friend method): 7 10 9 8 4 3 5 1 6 2
// 2. bool address		(friend method): 7 10 6 2 4|9 8 1 3 5
// 3. char address		(friend method): 7 9 10 8 1 2 3 4 5 6
// 4. first_character	(default operator): 7 9 10 1 2 3 4 5 6 8
