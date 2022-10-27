#include <stdio.h>

#include "buffer_proccesor.h"
#include "block_info.h"

void freeGarbage(void** pointers, int count)
{
    for (int i = 0; i < count; i++)
    {
        bufFree(pointers[i]);
    }
}

void test_Alloc3zonesFreeMiddle_Result_MiddleFreedOthersNotAffected()
{
    void* p1 = bufAlloc(1);
    bufShow("memAlloc(p1) [orig-size: 1]");

    void* p2 = bufAlloc(100);
    bufShow("memAlloc(p2) [orig-size: 100]");

    void* p3 = bufAlloc(30);
    bufShow("memAlloc(p2) [orig-size: 30]");

    bufFree(p2);
    bufShow("memFree(p2)");

    freeGarbage((void*[]){p1, p3}, 2);
}

int main()
{
    test_Alloc3zonesFreeMiddle_Result_MiddleFreedOthersNotAffected();

}
