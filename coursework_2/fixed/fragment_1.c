#include <stdlib.h>

int foo(int n, int b[], int size) {
    // FIX ARR32-C: validate VLA size before declaration
    if (n <= 0 || size <= 0 || n < size)
        return -1;

    int a[n], i;
    // FIX ARR30-C: loop bound changed from size+1 to size
    for (i = 0; i < size; i++) {
        a[i] = b[i];
    }
    return i;
}

int main() {
    int i;
    int b[100];
    // FIX EXP33-C: initialize b[] before use
    for (i = 0; i < 100; i++) {
        b[i] = 0;
    }
    for (i = 0; i < 100; i++) {
        b[i] = foo(i + 1, b, i);  // FIX ARR32-C: pass i+1 so n>=size always
    }
    for (i = 0; i < 100; i++) {
        if (b[i] != i) {
            return 1;
        }
    }
    return 0;
}