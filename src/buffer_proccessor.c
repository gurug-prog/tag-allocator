#include "buffer_proccesor.h"
#include "allocator.h"

void bufFill(char* bytes, size_t size)
{
    for (size_t i = 0; i < size; ++bytes, ++i)
    {
        *bytes = (char)rand();
    }
}

void* bufAlloc(size_t size)
{
    void* ptr = NULL;
    ptr = mem_alloc(size);
    if (ptr != NULL) bufFill(ptr, size);

    return ptr;
}

void* bufRealloc(void* ptr, size_t size)
{
    ptr = mem_realloc(ptr, size);
    if (ptr != NULL) bufFill(ptr, size);

    return ptr;
}

void bufShow(char* message)
{
    mem_show(message);
}
