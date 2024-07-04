void build()
{
    //what kind: 
    char what_kind[MAX] = {0}; 
    std::cout << "what kind of binary search tree:\nsimple\nAVL\nRBT (red black trees)\n"; std::cin.getline(s, MAX);
    
    
    int x = 0, how_many = 0;
    std::cout << "n == number of nodes = "; std::cin >> how_many; std::cout << '\n';
    if (how_many % 2 == 0)
    {
        std::cout << "it has to be a complete binary tree\n";
        return;
    }

    struct pointer_node {
        pointer_node* next;
        node* HEAP;
    };
    pointer_node* Q_first = nullptr;

    pointer_node* p = new pointer_node;
    p->next = nullptr;

    if (how_many)
    {
        std::cin >> x;
        root->val = x;
        how_many--;
        p->HEAP = root;
        Q_first = p;
    }

    node* tree = root;
    while (how_many)
    {
        //actualizez queue + creez for BinTree
        p = Q_first;
        bool first = 1;
        while (p)
        {
            node* L = new node, * R = new node;
            L->left = nullptr; L->right = nullptr;
            R->left = nullptr; R->right = nullptr;

            tree = p->HEAP;
            tree->left = L; tree->right = R;


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
                node* Parent = parent(p->HEAP, root);
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