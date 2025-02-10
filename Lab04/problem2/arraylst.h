//
// Created by Alex Brodsky on 2023-09-29.
//

#ifndef PROBLEM2_ARRAYLST_H
#define PROBLEM2_ARRAYLST_H

typedef struct arraylst {
    void **items;    /* pointer to an array of items */
    int size;        /* number of items stored in the array */
    int capacity;    /* maximum size of the array */
} arraylst_t;

/* Allocates a new string-list
 * parameter:
 *   capacity : posiitve integer denoting the maximum number of items in the list
 * returns:
 *   a pointer to the new list
 */
extern arraylst_t *arraylst_new(int capacity);

/* Adds a string to the end of the string-list
 * parameter:
 *   list : pointer to the list
 *   item : pointer to the string to be added
 * returns:
 *   index of the string on success or -1 on failure
 */
extern int arraylst_add(arraylst_t *list, void *item);

/* Gets the item at specified location in the string-list
 * parameter:
 *   list : pointer to the list
 *   idx : index of item to get.  0 <= idx < size
 * returns:
 *   pointer to item on success or NULL on failure
 */
extern void * arraylst_get(arraylst_t *list, int idx);

/* Removes the item at specified location in the item-list
 * parameter:
 *   list : pointer to the list
 *   idx : index of item to remove.  0 <= idx < size
 * returns:
 *   1 onf success and 0 on failure
 */
extern int arraylst_remove(arraylst_t *list, int idx);

/* Destroy the list, freeing the items array and the list struct.
 * parameter:
 *   list : pointer to the list
 * returns:
 *   None
 */
extern void arraylst_destroy(arraylst_t *list);

#endif //PROBLEM2_ARRAYLST_H
