//
// Created by Alex Brodsky on 2023-09-29.
//

#include <stdlib.h>
#include "arraylst.h"

extern arraylst_t *arraylst_new(int capacity) {
   arraylst_t *list = (arraylst_t *)malloc(sizeof(arraylst_t));
    if (!list) return NULL;

    list->items = malloc(capacity * sizeof(void *));

    list->size = 0;
    list->capacity = capacity;
    return list;
}

extern int arraylst_add(arraylst_t *list, void *item) {
    if (list->size >= list->capacity) return -1;
    list->items[list->size] = item;
    return list->size++;
}

extern void * arraylst_get(arraylst_t *list, int idx) {
    return list->items[idx];
}

extern int arraylst_remove(arraylst_t *list, int idx) {
    if (idx < 0 || idx >= list->size) return 0;

    for (int i = idx; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }

    list->size--;
    return 1;
}

extern void arraylst_destroy(arraylst_t *list) {
    free(list->items);
    free(list);
}
