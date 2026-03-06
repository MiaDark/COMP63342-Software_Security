#include <stdlib.h>

void myexit(int s) {
    _EXIT: goto _EXIT;
}

typedef struct node {
    int h;
    struct node *n;
} *List;

int main() {
    List a = (List)malloc(sizeof(struct node));
    if (a == 0) exit(1);
    List t;
    List p = a;
    a->h = 2;

    // Build list with non-deterministic length
    while (__VERIFIER_nondet_int()) {
        p->h = 1;
        t = (List) malloc(sizeof(struct node));
        if (t == 0) myexit(1);
        p->n = t;
        p = p->n;
    }

    p->h = 2;
    p->n = 0;
    p = a;
    while (p != 0) {
        if (p->h != 2)
        {
            ERROR: __VERIFIER_error();
        }
        p = p->n;
    }
    return 0;
}