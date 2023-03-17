#include "stack.h"
#include "file_utils.h"
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

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

int stack_cmp(Stack *s1, Stack *s2);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout)
{
    int cmp = 0;
    void *e = NULL;
    Stack *s_aux = NULL;

    if (!sin1 || !sin2 || !sout)
        return ERROR;

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        cmp = stack_cmp(sin1, sin2);
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

int stack_cmp(Stack *s1, Stack *s2)
{

    const float *float1 = NULL;
    const float *float2 = NULL;
    float1 = (float *)stack_top(s1);
    float2 = (float *)stack_top(s2);

    if (!s1 || !s2 || !float1 || !float2)
        return CMP_COMP;

    if (*float1 > *float2)
    {
        return EXIT_FAILURE;
    }
    else if (*float1 == *float2)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return RET_ERROR;
    }

    return CMP_COMP;
}

int main(int argc, char **argv)
{

    FILE *f = NULL;
    Stack *s1 = NULL;
    Stack *s2 = NULL;
    Stack *s = NULL;
    int i = 0, n1 = 0, n2 = 0;
    float ele = 0;
    float *fl = NULL;
    void *e = NULL;

    s1 = stack_init();
    s2 = stack_init();
    s = stack_init();

    if (!s1 || !s2 || !s)
        return EXIT_FAILURE;

    if (argc != 3)
        return EXIT_FAILURE;

    f = fopen(argv[1], "r");
    if (!f)
        return EXIT_FAILURE;

    fscanf(f, "%d", &n1);
    for (i = 0; i < n1; i++)
    {
        fscanf(f, "%f", &ele);
        fl = float_init(ele);
        stack_push(s1, fl);
    }

    fclose(f);

    f = fopen(argv[2], "r");
    if (!f)
        return EXIT_FAILURE;

    fscanf(f, "%d", &n2);
    for (i = 0; i < n2; i++)
    {
        fscanf(f, "%f", &ele);
        fl = float_init(ele);
        stack_push(s2, fl);
    }

    fprintf(stdout, "Ranking 0:\n");
    stack_print(stdout, s1, float_print);
    fprintf(stdout, "Ranking 1:\n");
    stack_print(stdout, s2, float_print);
    mergeStacks(s1, s2, s);
    fprintf(stdout, "Joint Ranking:\n");
    stack_print(stdout, s, float_print);

    fclose(f);

    while (stack_isEmpty(s) == FALSE)
    {
        e = stack_pop(s);
        float_free(e);
    }
    stack_free(s);
    while (stack_isEmpty(s1) == FALSE)
    {
        e = stack_pop(s1);
        float_free(e);
    }
    stack_free(s1);
    while (stack_isEmpty(s2) == FALSE)
    {
        e = stack_pop(s2);
        float_free(e);
    }
    stack_free(s2);

    return EXIT_SUCCESS;
}
