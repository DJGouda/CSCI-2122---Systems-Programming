//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "str_list.h"

extern strlist_list_t * strlist_new() {
    strlist_list_t * list = malloc(sizeof(strlist_list_t));
    return list;
}

extern void strlist_destroy(strlist_list_t *list) {
    assert(list != NULL);
    while (list->head != NULL) {
        strlist_node_t *tmp = list->head;
        list->head = list->head->next;
        free(tmp-> string); // free the srting as well
        free(tmp);
    }

    free(list);
}

static strlist_node_t *new_node(char *string, strlist_node_t *prev, strlist_node_t *next) {
    strlist_node_t *n = malloc(sizeof(strlist_node_t));
    if (n != NULL) {
        n->string = strdup(string); // Allocate and copy the string
        if (n->string == NULL) {
            free(n);
            return NULL;
        }
        n->prev = prev;
        n->next = next;
    }
    return n;
}


extern int strlist_add_front(strlist_list_t *list, char *string) {
    assert(list);

    strlist_node_t *n = new_node(string, NULL, list->head);
    if (n != NULL) {
        if (list->tail == NULL) {
            list->tail = n;
        } else {
            list->head->prev = n;
        }
        list->head = n;
    }
    return n != NULL;
}

extern int strlist_add_back(strlist_list_t *list, char *string) {
    assert(list);

    strlist_node_t *n = new_node(string, list->tail, NULL);
    if (n != NULL) {
        if (list->head == NULL) {
            list->head = n;
        } else {
            list->tail->next = n;
        }
        list->tail = n;
    }
    return n != NULL;
}

extern void strlist_remove_front(strlist_list_t *list) {
    assert(list);

    if (list->head != NULL) {
        strlist_node_t *n = list->head;
        list->head = list->head->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL; // the list is empty now
        }

        free(n->string); // free the string
        free(n);
    }
}

extern void strlist_remove_back(strlist_list_t *list) {
    assert(list);
    
    if (list->tail != NULL) {
        strlist_node_t *n = list->tail;
        list->tail = list->tail->prev;
        if (list->tail != NULL) { // should be != NULL
            list->tail->next = NULL;
        } else {
            list->head = NULL; // empty now
        }

        free(n->string); // free the string
        free(n);
    }
}

extern char * strlist_get_front(strlist_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->string;
    }
    return item;
}

extern char * strlist_get_back(strlist_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->tail != NULL) { // should be list->tail
        item = list->tail->string;
    }
    return item;
}


extern int ll_size(strlist_list_t *list) {
    assert(list);
    int count = 0;

    for (strlist_node_t *ptr = list->head; ptr != NULL; ptr = ptr->next) { // should iterate from list list->head, instead list->tail
        count++;
    }
    return count;
}

extern int ll_is_empty(strlist_list_t *list) {
    assert(list);
    return list->head == NULL;
}

extern int ll_insert(strlist_list_t *list, strlist_node_t *node, char *string) {
    assert(list);
    assert(node);

    if (node->next == NULL) {
        assert(list->tail == node);
        return strlist_add_back(list, string);
    } else {
        strlist_node_t *n = new_node(string, node, node->next);
        if (n != NULL) {
            node->next->prev = n;
            node->next = n;
        }
        return n != NULL;
    }
}


extern void ll_remove(strlist_list_t *list, strlist_node_t *node) {
    assert(list);
    assert(node);

    if (node->prev == NULL) {
        assert(list->head == node);
        strlist_remove_front(list); // function called was incorrect
    } else if(node->next == NULL) {
        assert(list->tail == node);
        strlist_remove_back(list); // function called was incorrect
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node->string); // free the string
        free(node);
    }
}
