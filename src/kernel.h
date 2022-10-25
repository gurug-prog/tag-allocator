#include <stddef.h>

void*   kernel_mem_alloc    (size_t size);
void*   kernel_mem_realloc  (void* ptr, size_t size);
void    kernel_mem_free     (void* ptr);
