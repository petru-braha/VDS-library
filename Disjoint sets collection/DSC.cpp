#include <iostream>
#include "backend_functions.h"
#include "specific_functions.h"

int main()
{
    construct_BFS();
    display(0, T[0].root);
    display(1, T[1].root);
    return 0;
}

/*

principle: until a certain position there is no empty spaces

values to try:
- 16 16 4 15 14 13 12 0 1 11 0 3 10 9 8 0 0 1 7 3 6 5 4 0 1 3 0 0 1 2 1 1
- 5 10 1 9 3 8 7 6 

functions: 
node* parent(node* n, node* search, int& which_child);
node* exists_node(node* n, int wanted);

void insert(int which_tree, node* n, int direction, int wanted);
void construct_BFS();
void delete_frontier(int which_tree, int wanted);//frunza

int height(node* n);
void display(int which_tree, node* nod);

*/