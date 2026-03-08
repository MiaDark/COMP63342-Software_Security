#include <stdlib.h>

int *a, *b;
int n;
#define BLOCK_SIZE 128

void foo() {
    int i;
    for (i = 0; i < n; i++)
        a[i] = -1;
    for (i = 0; i < BLOCK_SIZE - 1; i++)
        b[i] = -1;
}

int main() {
    n = BLOCK_SIZE;

    a = malloc(n * sizeof(*a));
    // FIX EXP34-C: check a before use
    if (a == NULL) return 1;

    b = malloc(n * sizeof(*b));
    // FIX EXP34-C: check b before use
    if (b == NULL) {
        free(a);
        return 1;
    }

    // FIX MEM30-C/MEM34-C: preserve original pointer for free()
    int *b_orig = b;
    *b++ = 0;

    foo();

    // FIX MEM30-C: free original pointer, not incremented one
    if (b[-1]) {
        free(a);
        free(b_orig);
    } else {
        free(a);
        free(b_orig);
    }
    return 0;
}
