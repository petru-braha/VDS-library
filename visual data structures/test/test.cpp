#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
#include "linked_list_tests.h"
// more directives


char choosen_structure[30];

void print_possibilities()
{
	std::cout << "0. array" << '\n'
		<< "1. linked_list" << '\n'
		<< "2. stack" << '\n'
		<< "3. queue" << '\n'
		<< "4. maxheap" << '\n'
		<< "5. minheap" << '\n'
		<< "6. trivial_tree" << '\n'
		<< "7. AVL_tree" << '\n'
		<< "8. red_black_tree" << '\n'
		<< "9. trie" << '\n'
		<< "0. graph" << '\n'
		<< "1. hash_table" << '\n';
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
	//::testing::GTEST_FLAG(filter) = strcat(choosen_structure, "*");

	int exit_status = RUN_ALL_TESTS();

	strt_visual();
	loop_visual();
	stop_visual();

	return exit_status;
}
