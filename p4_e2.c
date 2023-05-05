#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_queue.h"

#define MAX_LINE_LEN 1024

int cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int print_str(FILE *fp, const void *elem) {
    return fprintf(fp, "%s", (const char *)elem);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return EXIT_FAILURE;
    }

    SearchQueue *sq = search_queue_new(print_str, cmp_str);
    if (!sq) {
        fprintf(stderr, "Error creating search queue\n");
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, input)) {
        char *line_copy = strdup(line);
        if (!line_copy) {
            perror("Error allocating memory for line copy");
            break;
        }

        if (search_queue_push(sq, line_copy) == ERROR) {
            fprintf(stderr, "Error inserting line into search queue\n");
            free(line_copy);
            break;
        }
    }

    fclose(input);

    while (!search_queue_isEmpty(sq)) {
        char *min_line = search_queue_pop(sq);
        if (min_line) {
            print_str(output, min_line);
            free(min_line);
        }
    }

    fclose(output);
    search_queue_free(sq);
    return EXIT_SUCCESS;
}
