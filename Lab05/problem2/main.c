#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct {
    int amount;
    char name[20];
    float UnitCost;
} item_t;

void read_bill(linked_list_t *list) {
    int amount;
    char name[20];
    float UnitCost;

    while (scanf("%d %19s %f", &amount, name, &UnitCost) == 3 && amount > 0) {
        item_t *new_item = malloc(sizeof(item_t));

        if (!new_item) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        new_item->amount = amount;
        strcpy(new_item->name, name);
        new_item->UnitCost = UnitCost;

        ll_add_back(list, new_item);
    }
}

void merge_duplicates(linked_list_t *list) {
    ll_node_t *current = list->head;

    while (current) {
        item_t *current_item = (item_t *)current->item;
        if (current_item->amount == 0) {
            current = current->next;
            continue;
        }

        ll_node_t *checker = current->next;
        while (checker) {
            item_t *checker_item = (item_t *)checker->item;

            if (checker_item->amount > 0 &&
                strcmp(current_item->name, checker_item->name) == 0 &&
                current_item->UnitCost == checker_item->UnitCost) {
                
                current_item->amount += checker_item->amount;
                checker_item->amount = 0; 
            }

            checker = checker->next;
        }
        current = current->next;
    }
}

void print_bill(linked_list_t *list) {
    ll_node_t *current = list->head;

    while (current) {
        item_t *item = (item_t *)current->item;
        if (item->amount > 0) {
            printf("%d %s %.2f\n", item->amount, item->name, item->UnitCost); // used the hint
        }
        current = current->next;
    }
}

void free_bill(linked_list_t *list) {
    while (!ll_is_empty(list)) {
        item_t *item = (item_t *)ll_remove_front(list);
        free(item);
    }
    ll_destroy(list);
}

int main() {
    linked_list_t *list = ll_new();

    read_bill(list);
    merge_duplicates(list);
    print_bill(list);
    free_bill(list);

    return 0;
}