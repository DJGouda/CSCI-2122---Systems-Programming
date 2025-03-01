//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

/**********************************
 * See bottom of file for your work
 *********************************/

extern linked_list_t * ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t *list) {
    assert(list != NULL);
    while (list->head != NULL) {
        ll_node_t *tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }

    free(list);
}

static ll_node_t *new_node(void *item, ll_node_t *prev, ll_node_t *next) {
    ll_node_t *n = calloc(1, sizeof(ll_node_t));
    if (n != NULL) {
        n->item = item;
        n->prev = prev;
        n->next = next;
    }
    return n;
}


extern int ll_add_front(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,NULL, list->head);
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

extern int ll_add_back(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,list->tail, NULL);
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

extern void * ll_remove_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        ll_node_t *n = list->head;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }

        item = n->item;
        free(n);
    }
    return item;
}

extern void * ll_remove_back(linked_list_t *list) {
    assert(list);
    
    void *item = NULL;
    if (list->tail != NULL) {
        ll_node_t *n = list->tail;
        list->tail = list->tail->prev;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }

        item = n->item;
        free(n);
    }
    return item;
}

extern void * ll_get_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}


/************************************************************************
 * Your code below 
 ************************************************************************/

extern int ll_size(linked_list_t *list) {
    assert(list);
    
    int count = 0;
    ll_node_t *current = list->head;
    while (current) {
        count++;
        current = current->next;
    }
    
    return count;
}

extern int ll_is_empty(linked_list_t *list) {
    assert(list);
    
    return list->head == NULL ? 1 : 0;
}

extern int ll_insert(linked_list_t *list, ll_node_t *node, void *item) {
    assert(list);
    assert(node);

    ll_node_t *newNode = new_node(item, node, node->next);
    if (!newNode) return 0;

    if (node->next) {
        node->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    node->next = newNode;

    return 1;
}

extern void * ll_remove(linked_list_t *list, ll_node_t *node) {
    assert(list);
    assert(node);

    if (!node) return NULL;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    void *item = node->item;
    free(node);

    return item;
}
