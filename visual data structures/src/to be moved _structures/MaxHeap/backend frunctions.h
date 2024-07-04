// defines: MAX, maxheap (mh), heapify, build, propriety_array, display_root.
#define MAX 300
struct MH {
    int elem[MAX];
    int k;
} mh;

void heapify(int array[], int index, int n)
{
    int left = 2 * index + 1, right = 2 * index + 2, largest = 0;

    if (left < n && array[left] > array[index])
        largest = left;
    else
        largest = index;
    if (right < n && array[right] > array[largest])
        largest = right;
    if (largest != index)
    {
        int temp = array[index];
        array[index] = array[largest];
        array[largest] = temp;
        heapify(array, largest, n);
    }
}
void build()
{
    std::cout << "how many nodes: "; std::cin >> mh.k;
    if (mh.k % 2 == 0 && mh.k != 1)
    {
        std::cout << "it has to be a complete binary tree!\n";
        return;
    }

    std::cout << "please insert " << mh.k << " values: ";
    for (int i = 0; i < mh.k; i++)
        std::cin >> mh.elem[i];
    for (int i = mh.k / 2 - 1; i >= 0; i--)
        heapify(mh.elem, i, mh.k);
}
bool propriety_array(int array[], int index, int n)
{
    if (index == n)
        return true;
    else
    {
        if (array[index] < array[2 * index + 1] || array[index] < array[2 * index + 2])
            return false;
        return propriety_array(array, 2 * index + 1, n) && propriety_array(array, 2 * index + 2, n);
    }
}
void display_root()
{
    std::cout << "\n\n";

    int lvl = 0, i = 0, j = 1, index = 0;
    std::cout << "starting from the root:\n";
    while (index < mh.k)
    {
        std::cout << "level " << lvl++ << " : ";
        i = 0;
        while (i < j) //pe nivel
        {
            std::cout << mh.elem[(index - 1) / 2] << "->" << mh.elem[index] << ' ';
            i++; index++;
            if (!(index < mh.k))
                return;
        }

        std::cout << '\n';
        j *= 2;
    }
}

int height(int index);
void display(int index)
{
    std::cout << "\n\n";

    int h = height(index), maxlevel = height(0), lvl = maxlevel - h; //level e nivelul unde se situeaza nod

    struct pointer_node {
        pointer_node* next;
        int address;
    };
    pointer_node* Q_first = nullptr;

    pointer_node* p = new pointer_node; p->next = nullptr;
    p->address = index; Q_first = p;

    while (lvl < maxlevel)
    {
        std::cout << "level " << lvl << " contains the nodes: ";
        p = Q_first;

        bool first = 1;
        pointer_node* traversal = new pointer_node; traversal->next = nullptr;

        while (p && p->address<mh.k)//for each node from queue
        {
            if (p->address)//chack if it is the element, in that case the root has no parents
                std::cout << mh.elem[(p->address - 1) / 2] << "->" << mh.elem[p->address] << "   ";
            else
                std::cout << mh.elem[p->address] << "   ";

            //update queue
            //first child
            if (first)
            {
                traversal->address = p->address * 2 + 1;
                Q_first = traversal;
                first = 0;
            }
            else if (p->address * 2 + 1 < mh.k) {
                pointer_node* element = new pointer_node;
                element->address = p->address * 2 + 1;
                element->next = traversal->next;
                traversal->next = element;
                traversal = traversal->next;
            }

            //second child
            pointer_node* element = new pointer_node;
            element->address = p->address * 2 + 2;
            element->next = traversal->next;
            traversal->next = element;
            traversal = traversal->next;

            p = p->next;
        }

        std::cout << '\n'; lvl++;
    }
    std::cout << '\n';
}