#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* message = "Hello allocator!";

    int* iptr = malloc(sizeof(int));

    printf("%s\n", message);
    printf("%p\n", (void*)iptr);

    return 0;
}
