#include <stdlib.h>
#include "search_queue.h"
#include "bstree.h"

struct _SearchQueue {
    BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele) {
    SearchQueue *q = (SearchQueue *) malloc(sizeof(SearchQueue));
    if (!q) return NULL;
    q->data = tree_init(print_ele, cmp_ele);
    if (!q->data) {
        free(q);
        return NULL;
    }
    return q;
}

void search_queue_free(SearchQueue *q) {
    if (!q) return;
    tree_destroy(q->data);
    free(q);
}

Bool search_queue_isEmpty(const SearchQueue *q) {
    return (q && tree_isEmpty(q->data));
}

Status search_queue_push(SearchQueue *q, void *ele) {
    if (!q) return ERROR;
    return tree_insert(q->data, ele);
}

void *search_queue_pop(SearchQueue *q) {
    if (!q || search_queue_isEmpty(q)) return NULL;
    void *min = tree_find_min(q->data);
    tree_remove(q->data, min);
    return min;
}

void *search_queue_getFront(const SearchQueue *q) {
    if (!q) return NULL;
    return tree_find_min(q->data);
}

void *search_queue_getBack(const SearchQueue *q) {
    if (!q) return NULL;
    return tree_find_max(q->data);
}

size_t search_queue_size(const SearchQueue *q) {
    if (!q) return 0;
    return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q) {
    if (!q) return -1;
    return tree_inOrder(fp, q->data);
}
