#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_queue.h"

#define MAX_LINE_LEN 1024

int cmp_str(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

int print_str(FILE *fp, const void *elem)
{
    return fprintf(fp, "%s", (const char *)elem);
}

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    FILE *output = NULL;
    SearchQueue *sq = NULL;
    void *elem = NULL;
    char line[MAX_LINE_LEN];
    char *line_copy = NULL;
    char *min_line = NULL;
    Status st = OK;

    if (argc != 3)
        return EXIT_FAILURE;

    input = fopen(argv[1], "r");

    if (!input)
        return EXIT_FAILURE;

    output = fopen(argv[2], "w");
    if (!output)
    {
        fclose(input);
        return EXIT_FAILURE;
    }

    sq = search_queue_new(print_str, cmp_str);
    if (!sq)
    {
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    while (fgets(line, MAX_LINE_LEN, input) && st != ERROR)
    {
        line_copy = strdup(line);
        if (!line_copy)
        {
            st = ERROR;
        }

        if (search_queue_push(sq, line_copy) == ERROR)
        {
            st = ERROR;
        }
    }


    if (st == ERROR)
    {
        if (line_copy) 
        {
            free(line_copy);
        }

        while (!search_queue_isEmpty(sq))
        {
            elem = search_queue_pop(sq);
            if (elem)
            {
                free(elem);
            }
        }

        fclose(input);
        fclose(output); 
        search_queue_free(sq);
        return EXIT_FAILURE;
    }

    fclose(input);

    while (!search_queue_isEmpty(sq))
    {
        min_line = search_queue_pop(sq);
        if (min_line)
        {
            print_str(output, min_line);
            free(min_line);
        }
    }

    fclose(output);
    search_queue_free(sq);
    return EXIT_SUCCESS;
}
