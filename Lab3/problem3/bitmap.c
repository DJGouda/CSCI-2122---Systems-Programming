//
// Created by Alex Brodsky on 2023-09-21.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

extern char *bitmap_new(int size) {
    return calloc(1, (size + 7) >> 3);
}

/* YOUR CODE HERE
 */

int bitmap_test(char *bitmap, int i) {
    int byte_index = i / 8;
    int bit_index = i % 8;
    return (bitmap[byte_index] >> bit_index) & 1;
}

void bitmap_set(char *bitmap, int i) {
    int byte_index = i / 8;
    int bit_index = i % 8;
    bitmap[byte_index] |= (1 << bit_index);
}

void bitmap_reset(char *bitmap, int i) {
    int byte_index = i / 8;
    int bit_index = i % 8;
    bitmap[byte_index] &= ~(1 << bit_index);
}

void bitmap_toggle(char *bitmap, int i) {
    int byte_index = i / 8;
    int bit_index = i % 8;
    bitmap[byte_index] ^= (1 << bit_index);
}

void print_bitmap(char *bitmap, int size) {
    int num_bytes = (size + 7) / 8;
    for (int i = 0; i < num_bytes; i++) {
        printf("%02x ", (unsigned char)bitmap[i]);
    }
    printf("\n");
}