#define MAX 300
using namespace std;
struct node {
    int val;
    node* children[MAX] = { nullptr };
};
struct Tree {
    node* root;
} T[MAX];
void initialise_root(int which_tree, int value)
{
    node* n = new node;
    memset(n->children, 0, MAX);
    n->val = value;
    T[which_tree].root = n;
}

void insert(int which_tree, node* n, int direction, int wanted);
void construct_BFS()
{
    int j = 0, nr_tree = 0;
    cout << "cati copaci sa fie: "; cin >> j;
constr:
    cout << "\npentru copacul cu numarul: " << nr_tree << "\n\n";
    int x = 0, how_many = 0;
    cout << "cate noduri sa aiba: "; cin >> how_many;
    struct pointer_node {
        pointer_node* next;
        node* HEAP;
    };
    pointer_node* Q_first = nullptr;

    pointer_node* p = new pointer_node;
    p->next = nullptr;

    if (how_many)
    {
        cout << "valoare pt root: "; cin >> x;
        initialise_root(nr_tree, x);
        how_many--;
        p->HEAP = T[nr_tree].root;
        Q_first = p;
    }

    while (how_many)
    {
        p = Q_first;
        int nr_children = 0;
        bool first = 1;
        pointer_node* traversal = new pointer_node;
        traversal->next = nullptr;
        while (p && how_many)//pentru fiecare nod din queue doar daca trebuie sa mai adaugam noduri
        {   //clarificare eu iau un elem din queue si il transform in mai multe elemente 
            cout << "Nodul " << p->HEAP->val << " are n copii, unde n == "; cin >> nr_children;
            how_many -= nr_children;
            if (how_many < 0 || nr_children < 0)
            {
                cout << "wrong input\n";
                goto constr;
            }

            if (nr_children)//imi ignora pe cel care nu are copii pe cand nu ar trebui asa 
            {
                //valori
                for (int c = 0; c < nr_children; c++)
                {
                    cout << "pentru copilul cu numarul " << c << " , al nodului " << p->HEAP->val << " , inserez valoarea: "; cin >> x;
                    insert(nr_tree, p->HEAP, c, x);
                }

                //actualizare queue
                if (first)
                {
                    traversal->HEAP = p->HEAP->children[0];
                    Q_first = traversal;
                    first = 0;
                }
                else
                {
                    pointer_node* element = new pointer_node;
                    element->HEAP = p->HEAP->children[0];
                    element->next = traversal->next;
                    traversal->next = element;
                    traversal = traversal->next;
                }
                for (int c = 1; c < nr_children; c++)
                {
                    pointer_node* element = new pointer_node;
                    element->HEAP = p->HEAP->children[c];
                    element->next = traversal->next;
                    traversal->next = element;
                    traversal = traversal->next;
                }
            }

            p = p->next;
        }

        //sterg noduri in plus
        if (how_many == 0 && p)
        {
            p->HEAP = nullptr;
            delete(p->HEAP);
            p = p->next;
        }
    }
    nr_tree++;
    if (nr_tree < j)
        goto constr;
}

int height(node* n);
void display(int which_tree, node* nod)//pe height, fiecare nod va avea prefixul parintelui
{
    cout << "\n\n" << "pentru copacul cu numarul: " << which_tree << '\n';

    int h = height(nod), maxlevel = height(T[which_tree].root), level = maxlevel - h; //level e nivelul unde se situeaza nod

    struct pointer_node {
        pointer_node* next;
        pointer_node* parent;
        node* HEAP;
    };
    pointer_node* Q_first = nullptr;

    pointer_node* p = new pointer_node;
    p->next = nullptr;
    p->HEAP = T[which_tree].root;
    Q_first = p;

    int L = 0;
    bool output = 0;//daca se schimba la 1 se afisarea tot
    while (L < maxlevel)
    {
        if (L == level)
            output = 1;
        if (output)
            cout << "pe nivelul " << L << " avem nodurile: ";

        p = Q_first;
        bool first = 1;
        pointer_node* traversal = new pointer_node;
        traversal->next = nullptr;
        while (p)//pentru fiecare nod din queue
        {
            if (p->HEAP)//PATCH CA DACA PRIMUL NOD DIN COADA E NULL SE OPREA
            {
                //afisare
                if (output)
                {
                    if (L)
                        cout << p->parent->HEAP->val << ":" << p->HEAP->val << "   ";
                    else
                        cout << T[which_tree].root->val;
                }

                //actualizare queue
                if (first)
                {
                    traversal->HEAP = p->HEAP->children[0];
                    Q_first = traversal;
                    first = 0;

                    traversal->parent = p;
                }
                else
                {
                    if (p->HEAP->children[0])
                    {
                        pointer_node* element = new pointer_node;
                        element->HEAP = p->HEAP->children[0];
                        element->next = traversal->next;
                        traversal->next = element;
                        traversal = traversal->next;

                        traversal->parent = p;
                    }
                }
                for (int c = 1; p->HEAP->children[c]; c++)
                {
                    pointer_node* element = new pointer_node;
                    element->HEAP = p->HEAP->children[c];
                    element->next = traversal->next;
                    traversal->next = element;
                    traversal = traversal->next;

                    traversal->parent = p;
                }
            }

            p = p->next;
        }
        if (output)
            cout << '\n';
        L++;
    }

    cout << '\n';
}