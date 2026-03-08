#include <stdlib.h>
#define MAX_NODES 10  // explicit bound for ESBMC to fully unroll

void myexit(int s) {
    exit(s);
}
typedef struct node {
    int h;
    struct node *n;
} *List;
int main() {
    List a = (List)malloc(sizeof(struct node));
    if (a == NULL) exit(1);

    a->h = 2;
    a->n = 0;

    List p = a;
    int count = 0;

    while (__VERIFIER_nondet_int() && count < MAX_NODES) {
        List t = (List)malloc(sizeof(struct node));
        if (t == NULL) myexit(1);

        t->h = 2;
        t->n = 0;

        p->n = t;
        p = t;
        count++;
    }
    // Verify all nodes have h==2
    p = a;
    while (p != 0) {
        if (p->h != 2) {
            return 1;
        }
        p = p->n;
    }
    // FIX MEM31-C: free entire list
    p = a;
    while (p != 0) {
        List next = p->n;
        free(p);
        p = next;
    }
    return 0;
}