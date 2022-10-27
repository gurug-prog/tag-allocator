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

void test_ReallocToTheSameSize_Result_OriginalSizeNotAffected()
{
    void* p1 = bufAlloc(100);
    bufShow("memAlloc(p1) [orig-size: 100]");

    p1 = bufRealloc(p1, 100);
    bufShow("memRealloc(p1) [to-size: 100]");

    freeGarbage((void*[]){p1}, 1);
}

void test_ReallocToLessSize_Result_OriginalSizeDecreased()
{
    void* p1 = bufAlloc(300);
    bufShow("memAlloc(p1) [orig-size: 300]");

    p1 = bufRealloc(p1, 128);
    bufShow("memRealloc(p1) [to-size: 128]");

    freeGarbage((void*[]){p1}, 1);
}

void test_ReallocToBiggerSize_Result_OriginalSizeIncreased()
{
    void* p1 = bufAlloc(300);
    bufShow("memAlloc(p1) [orig-size: 300]");

    p1 = bufRealloc(p1, 1000);
    bufShow("memRealloc(p1) [to-size: 1000]");

    freeGarbage((void*[]){p1}, 1);
}

void test_FreeTwoNeighboursAreNotBusy_Result_BlocksMerged()
{
    void* p1 = bufAlloc(60);
    bufShow("memAlloc(p1) [orig-size: 60]");
    bufFree(p1);

    void* p2 = bufAlloc(128);
    bufShow("memAlloc(p2) [orig-size: 128]");

    void* p3 = bufAlloc(128);
    bufShow("memAlloc(p2) [orig-size: 128]");

    bufFree(p2);
    bufShow("merge (p1, p2):");

    freeGarbage((void*[]){p3}, 1);
}

void test_FreeBlockBetweenTwoNonBusy_Result_ThreeBlocksMerged()
{
    void* p1 = bufAlloc(156);
    void* p2 = bufAlloc(44);
    void* p3 = bufAlloc(20);
    bufShow("memAlloc (p1, p2, p3):");

    bufFree(p1);
    bufFree(p3);
    bufShow("memFree (p1, p3):");

    bufFree(p2);
    bufShow("Merge (p1, p2, p3):");

    freeGarbage(NULL, 0);
}

int main()
{
    printf("BLOCK HEADER SIZE: %d\n\n\n", (int)BLOCK_STRUCT_SIZE);
    test_ReallocToLessSize_Result_OriginalSizeDecreased();
    return 0;
}
