#include <stdio.h>
// #include "block.h"
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

static void* bufRealloc(void* ptr, size_t size)
{
    ptr = mem_realloc(ptr, size);
    if (ptr != NULL) bufFill(ptr, size);

    return ptr;
}

int main()
{
    void* p1 = bufAlloc(100);
    mem_show("memAlloc(p1):");

    bufAlloc(10);
    p1 = bufRealloc(p1, 100);
    mem_show("memRealloc(p1)");

    p1 = bufRealloc(p1, 1000);
    mem_show("memRealloc(p1)");
}
