//defines: build of the tree, display 

void construct_BFS(int how_many)
{
    int x = 0;
    struct pointer_node {
        pointer_node* next;
        node* HEAP;
    };
    pointer_node* Q_first = nullptr;

    pointer_node* p = new pointer_node;
    p->next = nullptr;

    if (how_many)
    {
        cin >> x;
        initialise_root(x);
        how_many--;
        p->HEAP = T.root;
        Q_first = p;
    }

    node* tree = T.root;
    while (how_many)
    {
        //actualizez queue + creez for BinTree
        p = Q_first;
        bool first = 1;
        while (p)
        {
            node* L = new node, * R = new node;
            L->left = nullptr;
            L->right = nullptr;
            R->left = nullptr;
            R->right = nullptr;

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

        //sterg nodurile create in plus
        if (how_many == 0)
        {
            while (p)
            {
                node* Parent = parent(p->HEAP, T.root);
                if (Parent->left == p->HEAP)
                    Parent->left = nullptr;
                else
                    Parent->right = nullptr;

                delete(p->HEAP);
                p = p->next;
            }
        }
    }
}

void display(node* nod)//2^nr noduri de pe ultimul rand-1
{
    cout << '\n';
    int identation = 1;
    for (int i = 0; i < height(T.root); i++)
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
    p->next = nullptr;
    p->HEAP = T.root;
    A.first = p;
    A.last = nullptr;
    A.nr_nodes = 1;

    while (identation >= 0 && level < h)
    {
        p = A.first;
        while (p)// AFISEZ
        {
            for (int i = 0; i < identation; i++)
                cout << "     ";//5 spatii

            //afisare valoare (val max:99999)
            if (p->HEAP == nullptr)//adica a fost stearsa frunza
                cout << "     ";
            else
            {
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
            }

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
            //transformare in cei 2 copii
            node_LLL* q = new node_LLL;
            if (p->HEAP)
            {
                q->HEAP = p->HEAP->right;
                p->HEAP = p->HEAP->left;
            }
            else
                q->HEAP = nullptr;

            q->next = p->next;
            p->next = q;

            //primul si ultimul 
            if (first)
            {
                A.first = p;
                first = 0;
            }
            A.last = p->next;
            p = p->next->next;
        }
    }
    cout << '\n';
}