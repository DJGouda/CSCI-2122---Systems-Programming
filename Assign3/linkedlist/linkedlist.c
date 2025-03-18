//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

typedef struct ll_node {
    struct ll_node *prev;
    struct ll_node *next;
    void *item;
} ll_node_t;

typedef struct linked_list {
    ll_node_t *head;
    ll_node_t *tail;
} linked_list;

typedef struct ll_iterator {
    linked_list_t list;  
    ll_node_t *current;  
    ll_node_t *prev;     
} ll_iterator;

extern linked_list_t ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
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


extern int ll_add_front(linked_list_t ll, void *item) {
    linked_list  *list = (linked_list *)ll;
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

extern int ll_add_back(linked_list_t ll, void *item) {
    linked_list  *list = (linked_list *)ll;
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

extern void * ll_remove_front(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
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

extern void * ll_remove_back(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
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

extern void * ll_get_front(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}

extern int ll_size(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);
    int count = 0;
    for (ll_node_t *ptr = list->head; ptr != NULL; ptr = ptr->next) {
        count++;
    }
    return count;
}

extern int ll_is_empty(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);
    return list->head == NULL;
}

/************************************************************************
 * Your code below 
 ************************************************************************/

extern ll_iterator_t  ll_iterator_new(linked_list_t list) {
    ll_iterator *iter = (ll_iterator *)calloc(1, sizeof(ll_iterator));
    if (iter == NULL) {
        return NULL;
    }
    iter->list = list;
    iter->current = NULL; 
    iter->prev = NULL;
    return iter;
}

extern void ll_iterator_destroy(ll_iterator_t iter) {
    free(iter);
}

extern void *ll_next(ll_iterator_t iter) {
    ll_iterator *it = (ll_iterator *)iter;
    linked_list *list = (linked_list *)it->list;

    if (it->current == NULL) {
        if (it->prev == NULL) {
            it->current = list->head;
        } else {
            it->current = it->prev->next;
        }
    } else {
        it->prev = it->current;
        it->current = it->current->next;
    }

    if (it->current == NULL) {
        return NULL;
    }

    return it->current->item;
}

extern int ll_has_next(ll_iterator_t iter) {
    ll_iterator *it = (ll_iterator *)iter;
    if (it->current == NULL) {
        return ((linked_list *)it->list)->head != NULL;
    }
    return it->current->next != NULL;
}

extern int ll_add(ll_iterator_t iter, void *item) {
    ll_iterator *it = (ll_iterator *)iter;
    linked_list *list = (linked_list *)it->list;

    ll_node_t *new_node = (ll_node_t *)calloc(1, sizeof(ll_node_t));
    if (new_node == NULL) {
        return 0; 
    }
    new_node->item = item;

    if (it->current == NULL) {
        new_node->next = list->head;
        if (list->head != NULL) {
            list->head->prev = new_node;
        }
        list->head = new_node;
        if (list->tail == NULL) {
            list->tail = new_node;
        }
    } else {
        new_node->prev = it->current;
        new_node->next = it->current->next;

        if (it->current->next != NULL) {
            it->current->next->prev = new_node;
        } else {
            list->tail = new_node; // If current is tail, update tail
        }
        it->current->next = new_node;
    }

    // Move to new node
    it->current = new_node;

    return 1; 

}

extern void *ll_set(ll_iterator_t iter, void *item) {
    ll_iterator *it = (ll_iterator *)iter;
    if (it->current == NULL || it->prev == NULL) {
        return NULL;
    }
    void *old_item = it->current->item;
    it->current->item = item;
    return old_item;
}

extern void *ll_remove(ll_iterator_t iter){
    ll_iterator *it = (ll_iterator *)iter;
    linked_list *list = (linked_list *)it->list;

    if (it->current == NULL) {
        return NULL;
    }

    ll_node_t *node_to_remove = it->current;
    void *item = node_to_remove->item;

    if (node_to_remove->prev != NULL) {
        node_to_remove->prev->next = node_to_remove->next;
    } else {
        list->head = node_to_remove->next;
    }

    if (node_to_remove->next != NULL) {
        node_to_remove->next->prev = node_to_remove->prev;
    } else {
        list->tail = node_to_remove->prev;
    }

    it->current = NULL; // when becomes null!!
    
    free(node_to_remove);
    return item;
}
