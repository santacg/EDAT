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

// mergeStacks(s1, s2, s3, int_cmp);

typedef int (*f_cmp)(const void *elem1, const void *elem2);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, f_cmp f);

int stack_cmp(Stack *s1, Stack *s2, f_cmp f);

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
    int i = 0, n = 0;
    char aux[MAX_CHAR] = "\0";
    Vertex *v = NULL;

    if (argc != 3)
        return EXIT_FAILURE;

    f = fopen(argv[1], "r");
    if (!f)
        return EXIT_FAILURE;

    s1 = stack_init();

    if (!s1)
    {
        stack_free(s1);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d", &n);
    while (fgets(aux, LINE, f) && i < n + 1)
    {
        if (strncmp("id", aux, 2) == 0)
        {
            v = vertex_initFromString(aux);
            if (stack_push(s1, v) == ERROR)
            {
                while (stack_isEmpty(s1) == FALSE)
                {
                    vertex_free(stack_pop(s1));
                }
                stack_free(s1);
                return EXIT_FAILURE;
            }
        }
        i++;
    }
    fclose(f);

    f = fopen(argv[2], "r");
    if (!f)
    {
        while (stack_isEmpty(s1) == FALSE)
        {
            vertex_free(stack_pop(s1));
        }
        stack_free(s1);
        return EXIT_FAILURE;
    }

    s2 = stack_init();
    if (!s2)
    {
        while (stack_isEmpty(s1) == FALSE)
        {
            vertex_free(stack_pop(s1));
        }
        stack_free(s1);
        stack_free(s2);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d", &n);
    i = 0;
    while (fgets(aux, LINE, f) && i < n + 1)
    {
        if (strncmp("id", aux, 2) == 0)
        {
            v = vertex_initFromString(aux);
            if (stack_push(s2, v) == ERROR)
            {
                while (stack_isEmpty(s1) == FALSE)
                {
                    vertex_free(stack_pop(s1));
                }
                stack_free(s1);
                while (stack_isEmpty(s2) == FALSE)
                {
                    vertex_free(stack_pop(s2));
                }
                stack_free(s2);
                return EXIT_FAILURE;
            }
        }
        i++;
    }

    s = stack_init();
    if (!s)
    {
        while (stack_isEmpty(s1) == FALSE)
        {
            vertex_free(stack_pop(s1));
        }
        stack_free(s1);
        while (stack_isEmpty(s2) == FALSE)
        {
            vertex_free(stack_pop(s2));
        }
        stack_free(s2);
        stack_free(s);
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Ranking 0:\n");
    stack_print(stdout, s1, vertex_print);
    fprintf(stdout, "Ranking 1:\n");
    stack_print(stdout, s2, vertex_print);
    if (mergeStacks(s1, s2, s, vertex_cmp) == ERROR)
    {
        while (stack_isEmpty(s1) == FALSE)
        {
            vertex_free(stack_pop(s1));
        }
        stack_free(s1);
        while (stack_isEmpty(s2) == FALSE)
        {
            vertex_free(stack_pop(s2));
        }
        stack_free(s2);
        while (stack_isEmpty(s) == FALSE)
        {
            vertex_free(stack_pop(s));
        }
        stack_free(s);
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Joint Ranking:\n");
    stack_print(stdout, s, vertex_print);

    fclose(f);

    while (stack_isEmpty(s) == FALSE)
    {
        vertex_free(stack_pop(s));
    }
    stack_free(s);
    while (stack_isEmpty(s1) == FALSE)
    {
        vertex_free(stack_pop(s1));
    }
    stack_free(s1);
    while (stack_isEmpty(s2) == FALSE)
    {
        vertex_free(stack_pop(s2));
    }
    stack_free(s2);

    return EXIT_SUCCESS;
}
