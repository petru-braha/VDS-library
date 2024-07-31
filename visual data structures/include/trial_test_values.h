#pragma once
#include <limits>
#define classic_size 10
#define maximum_size 15 // allowing for testing to insert five more elements

typedef const std::initializer_list<float> initializer;
initializer list_numbers				= { -1, 1.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };
const float block_numbers[maximum_size] = { -1, 1.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };

const std::initializer_list<const convoluted> list_objects = {

{ 5, true, "letters" },
{ 5, false, "letters" },
{ 4, true, "letters" },
{ 4, false, "letters" },
{ 5, true, "ladders_zzz" },
{ 5, false, "ladders_zzz" },
NULL,
{ 1, true, "z" },
{ 1, true, "a" },
{ 1, false, "a" }
};

// sorted using comparing method:
// - the following numbers represent the index of objects of type convoluted;
// 1. number - int		(friend method): 7 10 9 8 4 3 5 1 6 2
// 2. bool address		(friend method): 7 10 6 2 4|9 8 1 3 5
// 3. char address		(friend method): 7 9 10 8 1 2 3 4 5 6
// 4. first_character	(default operator): 7 9 10 1 2 3 4 5 6 8
