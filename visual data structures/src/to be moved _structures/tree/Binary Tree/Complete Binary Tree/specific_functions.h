bool exists_node(node* n, int wanted)
{
    if (n == NULL)
        return 0;
    return n->val == wanted ? 1 : 0 || exists_node(n->left, wanted) || exists_node(n->right, wanted);
}

void insert_BINTREE(node* n, bool direction, int wanted)
{
    if (n)
    {
        if (n->left && n->right)
        {
            cout << "BOSS! ARE DEJA 2 COPII\n";
            return;
        }
        if (n->left && direction == 0)
        {
            cout << "boss, pune la dreapta\n";
            return;
        }
        if (n->right && direction == 1)
        {
            cout << "boss, pune la stanga\n";
            return;
        }

        node* p = new node;
        p->left = NULL;
        p->right = NULL;
        p->val = wanted;

        if (direction)
            n->right = p;
        else
            n->left = p;
    }
    else
    {
        if (root == n)
        {
            initialise_root(wanted);
            return;
        }
        cout << "input gresit\n";
    }
}

int height(node* n)
{
    int h = 1;
    while (n->left != NULL)
    {
        n = n->left;
        h++;
    }
    return h;
}