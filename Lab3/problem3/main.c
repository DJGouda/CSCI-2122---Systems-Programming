//
// Created by Duren Gouda on 2025-02-02.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int main() {
    int M, N;

    // M (max number) and N (number of integers to follow)
    if (scanf("%d %d", &M, &N) != 2) {
        return 1; 
    }

    char *bitmap = bitmap_new(M + 1);
    if (!bitmap) {
        return 1; 
    }

    for (int i = 0; i < N; i++) {
        int num;
        if (scanf("%d", &num) != 1) {
            free(bitmap);
            return 1; 
        }
        bitmap_set(bitmap, num);
    }

    int max_start = -1, max_length = 0;
    int curr_start = -1, curr_length = 0;

    for (int i = 0; i <= M; i++) {
        if (bitmap_test(bitmap, i)) {
            if (curr_start == -1) { 
                curr_start = i;
                curr_length = 1;
            } else {
                curr_length++;
            }
        } else {
            if (curr_length > max_length) {
                max_start = curr_start;
                max_length = curr_length;
            }
            curr_start = -1;
            curr_length = 0;
        }
    }

    if (curr_length > max_length) {
        max_start = curr_start;
        max_length = curr_length;
    }

    printf("Max sequence:");
    for (int i = 0; i < max_length; i++) {
        printf(" %d", max_start + i);
    }
    printf("\n");

    free(bitmap); // used free() function seen from https://www.geeksforgeeks.org/free-function-in-c-library-with-examples/, how it is functioned

    return 0;
}
