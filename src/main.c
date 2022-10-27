#include <stdio.h>

#include "buffer_proccesor.h"
#include "block_info.h"

int main()
{
    void* p1 = bufAlloc(100);
    bufShow("memAlloc(p1):");

    bufAlloc(10);
    p1 = bufRealloc(p1, 100);
    bufShow("memRealloc(p1)");

    p1 = bufRealloc(p1, 1000);
    bufShow("memRealloc(p1)");
}
