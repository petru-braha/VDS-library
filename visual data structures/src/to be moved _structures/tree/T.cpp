#include <iostream>
#include "backend_functions.h"
#include "specific_functions.h"

node* parent(node* n, node* search, int& which_child);
node* exists_node(node* n, int wanted);

void insert(node* n, int direction, int wanted);
void construct_BFS();
void delete_frontier(int wanted);//leaf

int height(node* n);
void display(node* nod);

int main()
{
    construct_BFS();
    display(T.root);
    delete_frontier(1);
    display(T.root);
    return 0;
}
//16 16 4 15 14 13 12 0 1 11 0 3 10 9 8 0 0 1 7 3 6 5 4 0 1 3 0 0 1 2 1 1
//5 10 1 9 3 8 7 6 
