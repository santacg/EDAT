#include "stack.h"
#include "file_utils.h"
#include "vertex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
 **/

void clear_mstack(Stack *s);

typedef int (*f_cmp)(const void *elem1, const void *elem2);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, f_cmp f);

int stack_cmp(Stack *s1, Stack *s2, f_cmp f);

void clear_mstack(Stack *s)
{

    if (!s)
        return;

    while (stack_isEmpty(s) == FALSE)
    {
        vertex_free(stack_pop(s));
    }
    stack_free(s);
}

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, f_cmp f)
{
    int cmp = 0;
    void *e = NULL;
    Stack *s_aux = NULL;

    if (!sin1 || !sin2 || !sout)
        return ERROR;

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        cmp = stack_cmp(sin1, sin2, f);
        if (cmp == -2)
            return ERROR;

        if (cmp == 1)
        {
            e = stack_pop(sin1);
            if (!e)
                return ERROR;
        }
        else if (cmp == 0)
        {
            e = stack_pop(sin1);
            if (!e)
                return ERROR;
        }
        else
        {
            e = stack_pop(sin2);
            if (!e)
                return ERROR;
        }

        if (stack_push(sout, e) == ERROR)
            return ERROR;
    }

    s_aux = stack_init();
    if (!s_aux)
        return ERROR;

    if (stack_isEmpty(sin1) == FALSE)
    {
        while (stack_isEmpty(sin1) == FALSE)
        {
            e = stack_pop(sin1);
            if (stack_push(s_aux, e) == ERROR)
                return ERROR;
        }
    }
    else if (stack_isEmpty(sin2) == FALSE)
    {
        while (stack_isEmpty(sin2) == FALSE)
        {
            e = stack_pop(sin2);
            if (stack_push(s_aux, e) == ERROR)
                return ERROR;
        }
    }

    while (stack_isEmpty(s_aux) == FALSE)
    {
        e = stack_pop(s_aux);
        if (stack_push(sout, e) == ERROR)
            return ERROR;
    }

    stack_free(s_aux);

    return OK;
}

int stack_cmp(Stack *s1, Stack *s2, f_cmp f)
{

    if (!s1 || !s2)
        return RET_ERROR;

    return f(stack_top(s1), stack_top(s2));
}

int main(int argc, char **argv)
{

    FILE *f = NULL;
    Stack *s1 = NULL;
    Stack *s2 = NULL;
    Stack *s = NULL;
    int i = 0, n1 = 0, n2 = 0;
    char aux[MAX_CHAR*LINE] = "\0";
    Vertex *v = NULL;

    if (argc != 3)
        return EXIT_FAILURE;

    f = fopen(argv[1], "r");
    if (!f)
        return EXIT_FAILURE;

    s1 = stack_init();
    if (!s1)
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d", &n1);
    while (fgets(aux, LINE, f) && i < n1 + 1)
    {
        if (strncmp("id", aux, 2) == 0)
        {
            v = vertex_initFromString(aux);
            if (stack_push(s1, v) == ERROR)
            {
                clear_mstack(s1);
                fclose(f);
                return EXIT_FAILURE;
            }
        }
        i++;
    }
    fclose(f);

    fprintf(stdout, "Ranking 0:\n");
    fprintf(stdout, "Size:%d\n", n1);
    stack_print(stdout, s1, vertex_print);

    f = fopen(argv[2], "r");
    if (!f)
    {
        clear_mstack(s1);
        return EXIT_FAILURE;
    }

    s2 = stack_init();
    if (!s2)
    {
        clear_mstack(s1);
        fclose(f);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d", &n2);
    i = 0;
    while (fgets(aux, LINE, f) && i < n2 + 1)
    {
        if (strncmp("id", aux, 2) == 0)
        {
            v = vertex_initFromString(aux);
            if (stack_push(s2, v) == ERROR)
            {
                clear_mstack(s1);
                clear_mstack(s2);
                fclose(f);
                return EXIT_FAILURE;
            }
        }
        i++;
    }
    fclose(f);

    fprintf(stdout, "Ranking 1:\n");
    fprintf(stdout, "Size:%d\n", n2);
    stack_print(stdout, s2, vertex_print);

    s = stack_init();
    if (!s)
    {
        clear_mstack(s1);
        clear_mstack(s2);
        return EXIT_FAILURE;
    }

    if (mergeStacks(s1, s2, s, vertex_cmp) == ERROR)
    {
        clear_mstack(s1);
        clear_mstack(s2);
        clear_mstack(s);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Joint Ranking:\n");
    fprintf(stdout, "Size:%d\n", n1 + n2);
    stack_print(stdout, s, vertex_print);

    clear_mstack(s1);
    clear_mstack(s2);
    clear_mstack(s);

    return EXIT_SUCCESS;
}
