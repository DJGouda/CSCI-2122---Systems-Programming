#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "str_list.h"

static void clean_list(strlist_list_t *list) {
    for (strlist_node_t *n = list->head; n; n = n->next) {
        free(n->string);
    }
}

#define STRING_FORMAT "%31s"

int main() {
    setbuf(stdout, 0);

    char buffer[32];
    strlist_list_t *list = NULL;
    strlist_node_t *curr = NULL;

    while (scanf("%s", buffer) == 1) {
        int show_List = 1;

        if (!strcmp(buffer, "new")) {
            if (list) {
                clean_list(list);
                strlist_destroy(list);
            }
            list = strlist_new();
            assert(list);
        } else if (!strcmp(buffer, "append")) {
            assert(list);
            scanf(STRING_FORMAT, buffer);
            int success = strlist_add_back(list, buffer);
            if (!success) {
                printf("Failed to append \"%s\" to list\n", buffer);
            }
        } else if (!strcmp(buffer, "prepend")) {
            assert(list);
            scanf(STRING_FORMAT, buffer);
            int success = strlist_add_front(list, buffer);
            if (!success) {
                printf("Failed to prepend \"%s\" to list\n", buffer);
            }
        } else if (!strcmp(buffer, "front")) {
            assert(list);
            char *string = strlist_get_front(list);
            if (!string) {
                printf("Failed to get front of list\n");
            } else {
                printf("'%s' is at front of list\n", string);
                show_List = 0;
            }
        } else if (!strcmp(buffer, "back")) {
            assert(list);
            char *string = strlist_get_back(list);
            if (!string) {
                printf("Failed to get back of list\n");
            } else {
                printf("'%s' is at back of list\n", string);
                show_List = 0;
            }
        } else if (!strcmp(buffer, "remove_front")) {
            assert(list);
            strlist_remove_front(list);
        } else if (!strcmp(buffer, "remove_back")) {
            assert(list);
            strlist_remove_back(list);
        } else if (!strcmp(buffer, "destroy")) {
            strlist_destroy(list);
            list = NULL;
        } else if (!strcmp(buffer, "size")) {
            printf("List has %d items\n", ll_size(list));
            show_List = 0;
        } else if (!strcmp(buffer, "empty")) {
            if (ll_is_empty(list)) {
                printf("List is empty\n");
            } else {
                printf("List is not empty\n");
            }
            show_List = 0;
        } else if (!strcmp(buffer, "find")) {
            curr = NULL;
            scanf(STRING_FORMAT, buffer);
            for (strlist_node_t *n = list->head; n; n = n->next) {
                if(!strcmp(buffer, n->string)) {
                    curr = n;
                    break;
                }
            }

            if (!curr) {
                printf("'%s' not found in list\n", buffer);
            } else {
                printf("'%s' found in list\n", buffer);
                show_List = 0;
            }
        } else if (!strcmp(buffer, "insert")) {
            scanf("%s", buffer);
            if (curr) {
                int success = ll_insert(list, curr, buffer);
                if (!success) {
                    printf("Failed to insert '%s' after '%s' in list", buffer,
                           (char *)curr->string);
                }
            }
        } else if (!strcmp(buffer, "remove")) {
            if (curr) {
                ll_remove(list, curr);
            } else {
                printf("No node to remove.\n");
            }
        } else {
            break;
        }

        if (list && show_List) {
            printf("[");
            for (strlist_node_t *n = list->head; n; n = n->next) {
                printf(" %s", (char *)n->string);
            }
            printf(" ]\n");
        } else if (show_List) {
            printf("No list!\n");
        }
    }
    return 0;
}