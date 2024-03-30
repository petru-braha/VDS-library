//defines search, insert, delete, height
int search(int value)
{
    int index = mh.k - 1;
    while (index >= 0)
    {
        if (value <= mh.elem[index])
        {
            if (value == mh.elem[index])
                return index;
            else
            {
                for (int i = (index - 1) / 2; i < index * 2 + 1; i++)
                    if (mh.elem[i] == value)
                        return i;
                break;
            }
        }
        index = (index - 1) / 2;
    }
    std::cout << value << " was not found.\n";
    return -1;
}

void insert(int value)
{
    mh.elem[mh.k++] = value;
    int index = mh.k - 1;
    while (mh.elem[index] > mh.elem[(index - 1) / 2] && index)
    {
        int temp = mh.elem[index];
        mh.elem[index] = mh.elem[(index - 1) / 2];
        mh.elem[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

void del(int value)
{
    int index = search(value);
    if (index != -1)
    {
        //changing with the last element
        int temp = mh.elem[index];
        mh.elem[index] = mh.elem[mh.k - 1];
        mh.elem[mh.k - 1] = temp;
        mh.k--;
        heapify(mh.elem, index, mh.k);
    }
}

int height(int index)
{
    if (index >= mh.k)
        return 0;
    else
        return 1 + std::max(height(2 * index + 1), height(2 * index + 2));
}