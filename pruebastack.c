#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
    Stack *s = NULL;
    int *array = NULL;
    int i = 0, j = 0, n = 0;
    Status st;

    s = stack_init();
    if (!s) return EXIT_FAILURE;

    array = (int *) malloc(sizeof(int));
    for (i = 0; i < 2; i++) {
        n = rand() % 50;
        array[j] = n;
    }

    for (i = 0; i < 2; i++) {
        stack_push(s, array + i);
    }

}