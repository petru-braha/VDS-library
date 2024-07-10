
node* parent(node* n, node* search, int& which_child)
{
    if (n->children[0] == nullptr)
        return nullptr;
    else
    {
        which_child = 0;
        node* caregiver = nullptr;
        while (n->children[which_child])
        {
            if (n->children[which_child] == search)
            {
                caregiver = n;
                break;
            }
            caregiver = parent(n->children[which_child], search, which_child);
            if (caregiver)
                break;
            which_child++;
        }
        return caregiver;
    }//ideea e ca verific pentru fiecare nod ce copii are, dar trebuie sa verific si pt fiecare copil ce copii are;
}
node* exists_node(node* n, int wanted)
{
    if (n == nullptr)
        return nullptr;
    else
    {
        if (n->val == wanted)
            return n;

        int c = 0;
        node* found = nullptr;

        while (n->children[c])
        {
            found = exists_node(n->children[c], wanted);
            if (found)
                break;
            c++;
        }
        return found;
    }
}

void insert(int which_tree, node* n, int direction, int wanted)
{
    if (n)
    {
        if (n->children[direction])//se sch val
        {
            n->children[direction]->val = wanted;
            return;
        }

        node* p = new node;
        memset(p->children, 0, MAX);
        p->val = wanted;
        n->children[direction] = p;
    }
    else
    {
        if (T[which_tree].root == n)
        {
            initialise_root(which_tree, wanted);
            return;
        }
        cout << "input gresit\n";
    }
}

void delete_frontier(int which_tree, int wanted)
{
    node* one = exists_node(T[which_tree].root, wanted);
    if (one)
    {
        if (one->children[0])
            cout << "trebuie sa fie de la frontiera";
        else
        {
            int c = 0;
            node* deux = parent(T[which_tree].root, one, c); //deux is the caregiver to 
            while (deux->children[c + 1])
            {
                deux->children[c] = deux->children[c + 1];
                c++;
            }

            deux->children[c] = nullptr;
            delete(one);
        }
    }
    else
        cout << "nodul nu exista";
}

int height(node* n)
{
    if (n == nullptr)
        return 0;
    else
    {
        int c = 1;
        int h = 0, hmax = height(n->children[0]);
        while (n->children[c])
        {
            h = height(n->children[c]);
            hmax = max(h, hmax);
            c++;
        }
        return 1 + hmax;
    }
}