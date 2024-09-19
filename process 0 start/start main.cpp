#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <process.h>
#include <string>
#include <vector>

static std::vector<std::string> structure_names;

static void init()
{
	structure_names.push_back("array");
	structure_names.push_back("list");
	structure_names.push_back("stack");
	structure_names.push_back("queue");
	structure_names.push_back("avl");
	structure_names.push_back("red_black_tree");
	structure_names.push_back("maxheap");
	structure_names.push_back("minheap");
	structure_names.push_back("graph");
	structure_names.push_back("hash_table");
}

static void print()
{
	int i = 0;
	for (auto name : structure_names)
		printf("%d. %s\n", i++, name.c_str());
}

int main()
{
	int chosen_index = 0;
	init();
	print();

	printf("\nchoose the data structure by typing its index: ");
	scanf_s("%d", &chosen_index);

	if (chosen_index > 9 || chosen_index < 0)
	{
		printf("bad index.\n");
		return EXIT_FAILURE;

	}

	std::string argument = "*";
	argument += structure_names[chosen_index];
	argument += "*";

	_execl("../x64/Debug/process 1 test.exe", argument.c_str(), NULL);
	printf("lauching the unit tests failed.\n");
	return EXIT_FAILURE;
}
