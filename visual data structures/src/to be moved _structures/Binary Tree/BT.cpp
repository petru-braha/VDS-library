#include <iostream>
#include "specific_functions.h"
#include "backend_functions.h"

bool exists_node(node* n, int wanted);
node* adress(node* n, int wanted);
node* parent(node* wanted, node * root);

void insert_BINTREE(node* n, bool direction, int wanted);/* direction == 1 => right */
void construct_BFS(int how_many);
void delete_frontier(int wanted);

int height(node* n);
void display(node* nod);//maximum 5 digits

int main()
{
    int nr_variables = 0; cin >> nr_variables;
    construct_BFS(nr_variables);
    display(T.root);
    return 0;
}
//8 7 6 4 3 2 1 5