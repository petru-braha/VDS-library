#include <iostream>
#define MAX 300
using namespace std;
struct node {
    int val;
    node* left;
    node* right;
} *root;

void initialise_root(int value)
{
    node* n = new node;
    n->left = NULL;
    n->right = NULL;
    n->val = value;
    root = n;
}

void construct_BFS(int how_many)
{
    int x = 0;
    struct pointer_node {
        pointer_node* next;
        node* HEAP;
    };
    pointer_node* Q_first = NULL;

    pointer_node* p = new pointer_node;
    p->next = NULL;

    if (how_many)
    {
        cin >> x;
        initialise_root(x);
        how_many--;
        p->HEAP = root;
        Q_first = p;
    }

    node* tree = root;
    for (int i = 0; i < how_many; i++)
    {
        //actualizez queue + creez for BinTree
        p = Q_first;
        bool first = 1;
        while (p)
        {
            node* L = new node, * R = new node;
            L->left = NULL;
            L->right = NULL;
            R->left = NULL;
            R->right = NULL;

            tree = p->HEAP;
            tree->left = L;
            tree->right = R;


            //insert the value of right
            pointer_node* q = new pointer_node;
            q->HEAP = p->HEAP->right;

            q->next = p->next;
            p->next = q;

            //look at the left
            p->HEAP = p->HEAP->left;
            if (first)
            {
                Q_first = p;
                first = 0;
            }

            p = p->next->next;
        }

        //inserare
        p = Q_first;
        while (p && how_many)
        {
            cin >> x;
            p->HEAP->val = x;
            how_many--;
            p = p->next;
        }
    }
}

int height(node* n);
void display(node* nod)//2^nr noduri de pe ultimul rand-1
{
    cout << '\n';
    int identation = 1;
    for (int i = 0; i < height(root); i++)
        identation *= 2;
    identation--;

    int level = 0, h = height(nod);
    struct node_LLL
    {
        node_LLL* next;
        node* HEAP;
    };
    struct list_nodes ///like a preoder linked list
    {
        int nr_nodes;
        node_LLL* first;
        node_LLL* last;
    }A;

    node_LLL* p = new node_LLL;
    p->next = NULL;
    p->HEAP = root;
    A.first = p;
    A.last = NULL;
    A.nr_nodes = 1;

    while (identation >= 0 && level < h)
    {
        p = A.first;
        while (p)// AFISSEZ
        {
            for (int i = 0; i < identation; i++)
                cout << "     ";//5 spatii

            //afisare valoare (val max:99999)
            int nr_cif = 0, number = p->HEAP->val;
            while (number)
            {
                number /= 10;
                nr_cif++;
            }
            nr_cif = 5 - nr_cif;
            for (int i = 0; i < nr_cif; i++)
                cout << '0';
            cout << p->HEAP->val;

            for (int i = 0; i < identation + 1; i++)
                cout << "     ";

            p = p->next;
        }

        level++;
        identation /= 2;
        cout << '\n';

        //actualizare vector
        p = A.first;
        A.nr_nodes *= 2;
        bool first = 1;
        while (p)
        {
            //insert the value of right
            node_LLL* q = new node_LLL;
            q->HEAP = p->HEAP->right;

            q->next = p->next;
            p->next = q;

            //look at the left
            p->HEAP = p->HEAP->left;
            if (first)
            {
                A.first = p;
                first = 0;
            }

            //the same for the next
            A.last = p->next;
            p = p->next->next;
        }
    }
}