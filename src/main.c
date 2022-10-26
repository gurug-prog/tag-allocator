#include <stdio.h>

#include "allocator.h"

static void bufFill(char* bytes, size_t size)
{
    for (size_t i = 0; i < size; ++bytes, ++i)
    {
        *bytes = (char)rand();
    }
}

static void* bufAlloc(size_t size)
{
    void* ptr = NULL;
    ptr = mem_alloc(size);
    if (ptr != NULL) bufFill(ptr, size);

    return ptr;
}

int main()
{
    bufAlloc(10);
    mem_show("mem_alloc(10):");

    bufAlloc(16);
    mem_show("mem_alloc(16):");

    bufAlloc(100);
    mem_show("mem_alloc(100):");

    bufAlloc(225);
    mem_show("mem_alloc(225):");
}
