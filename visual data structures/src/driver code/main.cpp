#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <unordered_map>

// g++ -std=c++17 '.\visual data structures\src\main.cpp' -o bin/debug_start.exe

using std::cout, std::cin;
using std::string;

typedef std::unordered_map<int, string> map;
map visual_data_structures;

void print_possibilities()
{
	cout << "0. array" << '\n'
		<< "1. linked_list" << '\n'
		<< "2. stack" << '\n'
		<< "3. queue" << '\n'
		<< "4. maxheap" << '\n'
		<< "5. minheap" << '\n'
		<< "6. trivial_tree" << '\n'
		<< "7. AVL_tree" << '\n'
		<< "8. red_black_tree" << '\n'
		<< "9. trie" << '\n'
		<< "10. graph" << '\n'
		<< "11. hash_table" << '\n';
}

void init_names()
{
	visual_data_structures[0] = "array";
	visual_data_structures[1] = "linked_list";
	visual_data_structures[2] = "stack";
	visual_data_structures[3] = "queue";
	visual_data_structures[4] = "maxheap";
	visual_data_structures[5] = "minheap";
	visual_data_structures[6] = "trivial_tree";
	visual_data_structures[7] = "avl";
	visual_data_structures[8] = "red_black_tree";
	visual_data_structures[9] = "trie";
	visual_data_structures[10] = "graph";
	visual_data_structures[11] = "hash_table";
}

int main(int argc, char** argv)
{
	if (1 != argc)
	{
		std::cout << "the driver code does not take arguments.\n";
		exit(EXIT_FAILURE);
	}

	init_names();
	int choosen_index = 0;

	print_possibilities();
	cout << "\nchoose the data structure by typing its index: ";
	cin >> choosen_index;

	if (choosen_index > 11 || choosen_index < 0)
	{
		std::cout << "bad index.\n";
		exit(EXIT_FAILURE);

	}

	char argument[50] {};
	strcpy_s(argument, visual_data_structures.at(choosen_index).c_str());
	execl("a.exe", argument, NULL); // calls the compiled test.cpp with the argument

	std::cout << "lauching the project failed.\n";
	return EXIT_FAILURE;
}