//
// Created by Alex Brodsky on 2023-09-21.
//

#ifndef PROBLEM1_BITMAP_H
#define PROBLEM1_BITMAP_H

extern char *bitmap_new(int size);
extern int bitmap_test(char *bitmap, int i);
extern void bitmap_set(char *bitmap, int i);
extern void bitmap_reset(char *bitmap, int i);
extern void bitmap_toggle(char *bitmap, int i);

#endif //PROBLEM1_BITMAP_H
