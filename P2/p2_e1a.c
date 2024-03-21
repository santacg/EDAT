#include "stack.h"
#include "file_utils.h"
#include "types.h"
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

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

int stack_cmp(Stack *s1, Stack *s2);

void clear_mstack(Stack *s)
{

    if (!s)
        return;

    while (stack_isEmpty(s) == FALSE)
    {
        float_free(stack_pop(s));
    }
    stack_free(s);
}

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
            {
                break;
            }
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
    Status st = OK;

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
    for (i = 0; i < n1 && st == OK; i++)
    {
        fscanf(f, "%f", &ele);
        fl = float_init(ele);
        if (!fl)
        {
            st = ERROR;
        }
        if (stack_push(s1, fl) == ERROR)
        {
            st = ERROR;
        }
    }

    if (st == ERROR)
    {
        clear_mstack(s1);
        fclose(f);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Ranking 0:\n");
    stack_print(stdout, s1, float_print);
    fclose(f);

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
    for (i = 0, st = OK; i < n2 && st == OK; i++)
    {
        fscanf(f, "%f", &ele);
        fl = float_init(ele);
        if (!fl)
        {
            st = ERROR;
        }
        if (stack_push(s2, fl) == ERROR)
        {
            st = ERROR;
        }
    }

    if (st == ERROR)
    {
        clear_mstack(s1);
        clear_mstack(s2);
        fclose(f);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Ranking 1:\n");
    stack_print(stdout, s2, float_print);
    fclose(f);

    s = stack_init();
    if (!s)
    {
        clear_mstack(s1);
        clear_mstack(s2);
        return EXIT_FAILURE;
    }
    if (mergeStacks(s1, s2, s) == ERROR)
    {
        clear_mstack(s1);
        clear_mstack(s2);
        clear_mstack(s);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Joint Ranking:\n");
    stack_print(stdout, s, float_print);

    clear_mstack(s);
    clear_mstack(s1);
    clear_mstack(s2);

    return EXIT_SUCCESS;
}
