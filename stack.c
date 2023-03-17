#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
    void **item; /*!<Static array of elements*/
    int top; /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};

Stack * stack_init() {
    int i = 0;
    Stack *s = NULL;
    
    s = (Stack *) malloc(sizeof(Stack));
    if(!s) return NULL;

    s->item = NULL;
    s->top = -1;
    s->capacity = INIT_CAPACITY;

    return s;
}

void stack_destroy(Stack *s) {
    if (!s) return;

    free(s);
}

Status stack_push(Stack *s, const void *ele) {
    
    if (!s || !ele) return ERROR;

    if (s->top == s->capacity) {
        s->item = (void *) realloc(s->item, sizeof(void) * FCT_CAPACITY);
        s->capacity = s->capacity * FCT_CAPACITY;
    }

    s->top++;
    s->item = ele;

    return OK;
}

void * stack_pop(Stack *s) {
    void *ele = NULL;

    if (!s || (stack_isEmpty(s) == TRUE)) return NULL;

    ele = s->item[s->top];
    s->top--;

    return ele;
}


void * stack_top(const Stack *s) {
    void *ele = NULL;

    if (!s) return NULL;

    ele = s->item;

    return ele;
}

Bool stack_isEmpty(const Stack *s) {

    if (!s) return FALSE;

    if (s->top == -1) {
        return TRUE;
    }

    return FALSE;
}

