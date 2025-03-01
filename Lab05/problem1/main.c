#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

static void clean_list(linked_list_t *list) {
    for (ll_node_t *n = list->head; n; n = n->next) {
        free(n->item);
    }
}

int main() {
    char buffer[100];
    linked_list_t *list = NULL;
    ll_node_t *curr = NULL;

    while (scanf("%s", buffer) == 1) {
        if (!strcmp(buffer, "new")) {
            if (list) {
                clean_list(list);
                ll_destroy(list);
            }
            list = ll_new();
            assert(list);
        } else if (!strcmp(buffer, "append")) {
            assert(list);
            scanf("%s", buffer);
            char * string = strdup(buffer);
            int success = ll_add_back(list, string);
            if (!success) {
                printf("Failed to append \"%s\" to list\n", string);
                free(string);
            }
        } else if (!strcmp(buffer, "prepend")) {
            assert(list);
            scanf("%s", buffer);
            char * string = strdup(buffer);
            int success = ll_add_front(list, string);
            if (!success) {
                printf("Failed to prepend \"%s\" to list\n", string);
                free(string);
            }
        } else if (!strcmp(buffer, "front")) {
            assert(list);
            char *string = ll_get_front(list);
            if (!string) {
                printf("Failed to get front of list\n");
            } else {
                printf("'%s' is at front of list\n", string);
            }
        } else if (!strcmp(buffer, "back")) {
            assert(list);
            char *string = ll_get_back(list);
            if (!string) {
                printf("Failed to get back of list\n");
            } else {
                printf("'%s' is at back of list\n", string);
            }
        } else if (!strcmp(buffer, "remove_front")) {
            assert(list);
            char *string = ll_remove_front(list);
            if (!string) {
                printf("Failed to remove from front of list\n");
            } else {
                free(string);
            }
        } else if (!strcmp(buffer, "remove_back")) {
            assert(list);
            char *string = ll_remove_back(list);
            if (!string) {
                printf("Failed to remove from back of list\n");
            } else {
                free(string);
            }
        } else if (!strcmp(buffer, "destroy")) {
            for (ll_node_t *n = list->head; n; n = n->next) {
                free(n->item);
            }
            ll_destroy(list);
            list = NULL;
        } else if (!strcmp(buffer, "size")) {
            printf("List has %d items\n", ll_size(list));
        } else if (!strcmp(buffer, "empty")) {
            if (ll_is_empty(list)) {
                printf("List is empty\n");
            } else {
                printf("List is not empty\n");
            }
        } else if (!strcmp(buffer, "find")) {
            curr = NULL;
            scanf("%s", buffer);
            for (ll_node_t *n = list->head; n; n = n->next) {
                if(!strcmp(buffer, n->item)) {
                    curr = n;
                    break;
                }
            }

            if (!curr) {
                printf("'%s' not found in list\n", buffer);
            } else {
                printf("'%s' found in list\n", buffer);
            }
        } else if (!strcmp(buffer, "insert")) {
            scanf("%s", buffer);
            if (curr) {
                char *string = strdup(buffer);
                int success = ll_insert(list, curr, string);
                if (!success) {
                    printf("Failed to insert '%s' after '%s' in list", string,
                           (char *)curr->item);
                    free(string);
                }
            } else {
                printf("No node to insert after.\n");
            }
        } else if (!strcmp(buffer, "remove")) {
            if (curr) {
                char *string = ll_remove(list, curr);
                if (!string) {
                    printf("Failed to remove '%s' in list", (char *)curr->item);
                } else {
                    free(string);
                }
            } else {
                printf("No node to remove.\n");
            }
        } else {
            break;
        }

        if (list) {
            printf("[");
            for (ll_node_t *n = list->head; n; n = n->next) {
                printf(" %s", (char *)n->item);
            }
            printf(" ]\n");
        } else {
            printf("No list!\n");
        }
    }
    return 0;
}