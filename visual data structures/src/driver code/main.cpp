#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <process.h>
#include <string>
#include <vector>

static std::vector<std::string> visual_data_structures;

static void init()
{
	visual_data_structures.push_back("array");
	visual_data_structures.push_back("list");
	visual_data_structures.push_back("stack");
	visual_data_structures.push_back("queue");
	visual_data_structures.push_back("avl");
	visual_data_structures.push_back("red_black_tree");
	visual_data_structures.push_back("maxheap");
	visual_data_structures.push_back("minheap");
	visual_data_structures.push_back("graph");
	visual_data_structures.push_back("hash_table");
}

static void print()
{
	int i = 0;
	for (auto name : visual_data_structures)
		printf("%d. %s\n", i++, name.c_str());
}

int main()
{
	int chosen_index = 0;
	init();
	print();

	printf("\nchoose the data structure by typing its index: ");
	scanf("%d", &chosen_index);

	if (chosen_index > 9 || chosen_index < 0)
	{
		printf("bad index.\n");
		exit(EXIT_FAILURE);

	}

	std::string argument = visual_data_structures[chosen_index] += "*"; 
	_execl("x64/Debug/visual data structures.exe", "head_argument", argument.c_str(), NULL);
	printf("lauching the project failed.\n");
	return EXIT_FAILURE;
}
