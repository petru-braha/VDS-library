#pragma once
#include "maxheap.h"
#include "maxheap.cpp"

//------------------------------------------------
// primitives:

TEST(maxheap_p, initialisation)
{
	std::initializer_list<int> list{ 100, 200, 300, 400 };
	maxheap<> a = 5;
}

//------------------------------------------------
// convoluted types:

TEST(maxheap_c, initialisation)
{

}
