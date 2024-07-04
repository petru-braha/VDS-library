#include "backend_functions.h"
#include "specific_functions.h"

int main()
{
    int nr_variables = 0;
    cin >> nr_variables;
    construct_BFS(nr_variables);
    display(root);

    return 0;
}

/*
functions:

bool exists_node(node* n, int wanted);
void insert_BINTREE(node* n, bool direction, int wanted);
void construct_BFS(int how_many);

no delete function: it won't be a complete binary tree

int height(node* n);
void display(node* nod);//maximmum 5 digits
*/