#pragma once
#include "maxheap.h"
#include "maxheap.cpp"

TEST(maxheap, da){
	std::initializer_list<int> list{ 100, 200, 300, 400 };
	maxheap<> a = 5;
	maxheap<> b = list;
	b.prnt();
	std::cout << "\n";
}