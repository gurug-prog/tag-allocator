#include <stdio.h>
// #include <stdlib.h>

#include "allocator_impl.h"

int main()
{
    for (size_t i = 1; i < 50; ++i)
    {
        printf("%zu -> %zu\n", i, ROUND_BYTES(i));
    }
}
