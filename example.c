#include <stdio.h>
#include <string.h>
#include "dsalloc.h"

struct Junk {
    int number;
    double annoying_number;
};

// Handy function for making junk
char *make_junk(DSAllocator a)
{
    const char *str = "Look ma! I'm allocatin'!";
    char *junk_str = dsalloc(a, strlen(str) + 1);
    strcpy(junk_str, str);

    // We're not even going to use this. What a waste!
    struct Junk *junk = dsalloc(a, sizeof(*junk));

    return junk_str;
}

int main()
{
    DSAllocator a = dsalloc_new();

    // Allocate some junk
    printf("%s\n", make_junk(a));

    printf("%lu bytes of heap-allocated memory\n", dsalloc_memory_usage(a));
    printf("%lu bytes of allocator overhead\n", dsalloc_overhead(a));

    // Throw out all of the junk we just allocated
    dsalloc_delete(a);

    // No leaks!
    return 0;
}

