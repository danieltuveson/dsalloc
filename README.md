# dsalloc - dan's shitty allocator

If you just dump malloc'd memory into a linked list, it's not a memory leak!

To build, just run `make`. See `dsalloc.h` for usage.

## Example
``` C
#include <stdio.h>
#include <string.h>
#include "dsalloc.h"

struct Junk {
    int number;
    double annoying_number;
};

int main(void)
{
    DSAllocator a = dsalloc_new();

    // Allocate some junk
    const char *str = "Look ma! I'm allocatin'!";
    char *junk_str = dsalloc(a, strlen(str) + 1);
    strcpy(junk_str, str);
    printf("%s\n", junk_str);

    // We're not even going to use this. What a waste!
    struct Junk *junk = dsalloc(a, sizeof(*junk));

    printf("%lu bytes of heap-allocated memory\n", dsalloc_memory_usage(a));
    printf("%lu bytes of allocator overhead\n", dsalloc_overhead(a));

    // Throw out all of the junk we just allocated
    dsalloc_delete(a);

    // No leaks!
    return 0;
}
```
To build the example code, run `make example`. If we run `valgrind ./example`, we get the following:
``` sh
==2960== Memcheck, a memory error detector
==2960== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==2960== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==2960== Command: ./example
==2960==
Look ma! I'm allocatin'!
41 bytes of heap-allocated memory
56 bytes of allocator overhead
==2960==
==2960== HEAP SUMMARY:
==2960==     in use at exit: 0 bytes in 0 blocks
==2960==   total heap usage: 6 allocs, 6 frees, 1,121 bytes allocated
==2960==
==2960== All heap blocks were freed -- no leaks are possible
==2960==
==2960== For lists of detected and suppressed errors, rerun with: -s
==2960== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Hooray! No leaks!

<sub><sub>For the curious, the extra 1024 bytes of memory that valgrind reported are from calling `printf`. Your libc implementation may allocate a different amount when doing buffered io.</sub></sub>
