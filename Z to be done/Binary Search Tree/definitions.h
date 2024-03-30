#include <iostream>
#define MAX 300
struct node {
	int value;
	node* left, * right;
};

struct RBT_node {
	int value;
	RBT_node* left, * right;
	bool color; //0 == black and 1 == red
};