#include <stddef.h>

void*   bufAlloc        (size_t size);
void    bufFree         (void* ptr);
void    bufFill         (char* bytes, size_t size);
void*   bufRealloc      (void* ptr, size_t size);
void    bufShow         (char* message);
