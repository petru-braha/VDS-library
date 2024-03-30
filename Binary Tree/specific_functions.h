//defines: the structure of the tree + initialisation, checking if a node exists, address, parent, insertion, deletion, height
#define MAX 300
using namespace std;
struct node {
    int val;
    node* left;
    node* right;
};
struct BinaryTree {
    node* root;
} T;
void initialise_root(int value)
{
    node* n = new node;
    n->left = nullptr;
    n->right = nullptr;
    n->val = value;
    T.root = n;
}

bool exists_node(node* n, int wanted)
{
    if (n == nullptr)
        return 0;
    else
    {
        return n->val == wanted ? 1 : 0 || exists_node(n->left, wanted) || exists_node(n->right, wanted);
    }
    //it is pointeless to return the path to a node; therefore no more functions that return the path to a node
}

node* adress(node* n, int wanted)
{
    if (n == nullptr)
        return nullptr;
    else
    {
        if (n->val == wanted)
            return n;
        if (adress(n->left, wanted))
            return adress(n->left, wanted);
        else
            return adress(n->right, wanted);
    }

}
node* parent(node* wanted, node* root)
{
    if (root == nullptr)
        return nullptr;
    else
    {
        if (root->left == wanted || root->right == wanted)
            return root;
        if (parent(wanted, root->left))
            return parent(wanted, root->left);
        else
            return parent(wanted, root->right);
    }
}

void insert_BINTREE(node* n, bool direction, int wanted)/* direction == 1 => right */
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
        p->left = nullptr;
        p->right = nullptr;
        p->val = wanted;

        if (direction)
            n->right = p;
        else
            n->left = p;
    }
    else
    {
        if (T.root == n)
        {
            initialise_root(wanted);
            return;
        }
        cout << "input gresit\n";
    }
}

void delete_frontier(int wanted)
{
    node* nod = adress(T.root, wanted);
    if (nod)
    {
        node* Parent = parent(nod, T.root);
        if (Parent->left == nod)
            Parent->left = nullptr;
        else
            Parent->right = nullptr;
        delete(nod);
    }
}

int height(node* n)
{
    if (n == nullptr)
        return 0;
    else
    {
        return 1 + max(height(n->left), height(n->right));
    }
}
