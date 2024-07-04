#include <iostream>
#include "pch.h"

std::string structure="";

void list_structures()
{
	std::cout << "The list of data structures:\n";
	std::cout << "- Binary Tree\n"
		<< "- MaxHeap\n"
		<< "- Regular tree\n"
		<< "- AVL\n"
		<< "- Black Red tree\n"
		<< "- disjoint set collection: with trees\n"
		<< "- Hash Table - lists\n"
		<< "- Hash Table - other metods\n"
		<< "- Digital tree - tries\n\n";
	std::cout << "Type the chosen D.S.: "; std::cin >> structure;
}