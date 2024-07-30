#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
// more directives


char choosen_structure[30];

void print_possibilities()
{
	std::cout << "0. array" << '\n'
		<< "1. hash_table" << '\n'
		<< "2. linked_list" << '\n'
		<< "3. stack" << '\n'
		<< "4. queue" << '\n'
		<< "5. maxheap" << '\n'
		<< "6. minheap" << '\n'
		<< "7. trivial_tree" << '\n'
		<< "8. AVL_tree" << '\n'
		<< "9. red_black_tree" << '\n'
		<< "0. trie" << '\n'
		<< "1. graph" << '\n'
		<< "2. map" << '\n';
}

void choose_structure()
{
	std::cout << "choose your data structure: " << '\n';
	print_possibilities();
	std::cin >> choosen_structure;
}

void strt_visual() {}
void loop_visual() {}
void stop_visual() {}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	//choose_structure();
	::testing::GTEST_FLAG(filter) = strcat(choosen_structure, "*");

	int exit_status = RUN_ALL_TESTS();

	strt_visual();
	loop_visual();
	stop_visual();
	
	return exit_status;
}	
