#pragma once
#include "linked_list.cpp"

//------------------------------------------------
// primitives:

TEST(linked_list_p, initialisation)
{
	linked_list<> a;
	linked_list<int> b{ 100, 200, 300, 400, 500 };
	char text[6] = "hello";
	linked_list<char> c(text);
	linked_list<char> d(c);
	linked_list<char> e(linked_list<char>(d));
}

