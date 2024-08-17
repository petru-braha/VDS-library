#pragma once
#include <limits>
#define classic_size 10
#define maximum_size 15 // allowing for testing to insert five more elements

// for initialization:
typedef const std::initializer_list<float> initializer;
initializer list_numbers				= { -1, 1.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };
const float block_numbers[maximum_size] = { -1, 1.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f };

// for insertion:
const float insertions[5] = { 10.5f, 10.6f, 10.4f, 10.8f, 10.7f }; // index: 0 1 0 end 3 
initializer final_numbers = { 10.4f, 10.5f, 10.6f, 10.7f, -1, 1.01f, 1, UCHAR_MAX, USHRT_MAX, LONG_MIN, -1.01f, -0.99f, 0.99f, 1.01f, 10.8f };

//------------------------------------------------
// convoluted type:

const convoluted list_objects[maximum_size] = {

{ 20, true, "lettera\0"},
{ 18, false, "lettera\0" },
{ 18, true, "letterb\0" },
{ 19, false, "letterb\0" },
{ 12, true, "letterzzz\0" },
{ 14, false, "letterzzz\0" },
NULL,
{ 13, true, "z\0" },
{ 15, true, "a\0" },
{ 16, false, "a\0" }
};

// indexes of the sorted 'list_objects' using the friend comparing methods:
// 1. number - int: { 6, 4, 7, 5, 8, 9, 1, 2, 3, 0 }
// 2. bool address: { 6, 9, 1, 3, 5, 8, 0, 2, 4, 7 }
// 3. char address: { 6, 8, 9, 0, 1, 2, 3, 4, 5, 7 }

// sorting test and queries test
// the corectness of the code is proven by the first test which will take into account all comparing methods.
// to avoid redundancy in the second one, only one will be considered into the analysis.