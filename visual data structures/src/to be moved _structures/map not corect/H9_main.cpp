#include <stdio.h>
#include "H9_map.h"
#include "H9_map.cpp"
#include "map_iterator.cpp"

int H9_map_main()
{
    Map<int, const char*> m;
    m[10] = "C++";
    m[20] = "test";
    m[30] = "Poo";
    m.print(30); printf("\n");
    
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    m[20] = "result";
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    
    return 0;
}