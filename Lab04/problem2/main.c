#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "arraylst.h"

int main() {
    char buffer[100];
    arraylst_t *list = NULL;

    while (scanf("%s", buffer) == 1) {
        if (!strcmp(buffer, "new")) {
            int capacity;

            if (list) {
                arraylst_destroy(list);
            }

            scanf("%d", &capacity);
            list = arraylst_new(capacity);
            assert(list);
            assert(capacity == list->capacity);
        } else if (!strcmp(buffer, "add")) {
            assert(list);
            scanf("%s", buffer);
            char * string = strdup(buffer);
            int idx = arraylst_add(list, string);
            if (idx < 0) {
                printf("Failed to add \"%s\" to list\n", string);
                free(string);
            }
        } else if (!strcmp(buffer, "get")) {
            int idx;
            assert(list);
            scanf("%d", &idx);
            char *string = arraylst_get(list, idx);
            if (!string) {
                printf("Failed to get at index %d in list\n", idx);
            }
        } else if (!strcmp(buffer, "remove")) {
            int idx;
            assert(list);
            scanf("%d", &idx);
            char *string = arraylst_get(list, idx);
            if (!string) {
                printf("Failed to find string at index %d to remove from list\n", idx);
            } else {
                arraylst_remove(list, idx);
            }
        } else if (!strcmp(buffer, "destroy")) {
            arraylst_destroy(list);
            list = NULL;
        } else {
            break;
        }

        if (list) {
            printf("(%d/%d) [", list->size, list->capacity);
            for (int i = 0; i < list->size; i++) {
                printf(" %s", (char *)arraylst_get(list, i));
            }
            printf(" ]\n");
        } else {
            printf("No list!\n");
        }
    }
    return 0;
}