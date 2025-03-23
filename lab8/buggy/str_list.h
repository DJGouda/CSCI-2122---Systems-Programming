//
// Created by Alex Brodsky on 2023-09-20.
//

#ifndef STRING_LIST__H
#define STRING_LIST__H

typedef struct strlist_node {
    char *string;
    struct strlist_node *prev;
    struct strlist_node *next;
} strlist_node_t;

typedef struct str_list {
    strlist_node_t *head;
    strlist_node_t *tail;
} strlist_list_t;

extern strlist_list_t * strlist_new();
extern void strlist_destroy(strlist_list_t *list);
extern int strlist_add_front(strlist_list_t *list, char *string);
extern int strlist_add_back(strlist_list_t *list, char *string);
extern char * strlist_get_front(strlist_list_t *list);
extern char * strlist_get_back(strlist_list_t *list);

extern void strlist_remove_front(strlist_list_t *list);
extern void strlist_remove_back(strlist_list_t *list);

extern int ll_size(strlist_list_t *list);
extern int ll_is_empty(strlist_list_t *list);
extern int ll_insert(strlist_list_t *list, strlist_node_t *node, char *string);
extern void ll_remove(strlist_list_t *list, strlist_node_t *node);


#endif //STRING_LIST__H
