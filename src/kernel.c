#include <stdlib.h>

void* kernel_mem_alloc(size_t size)
{
    return malloc(size);
}

void* kernel_mem_realloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void kernel_mem_free(void* ptr)
{
    return free(ptr);
}
