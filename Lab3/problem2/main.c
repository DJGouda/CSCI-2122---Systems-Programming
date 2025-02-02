//
// Created by Duren Gouda on 2025-02-02.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int main() {
    int M, N;

    // M (max integer) and N (number of integers to follow)
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
        bitmap_toggle(bitmap, num);
    }

    printf("Odd:");
    for (int i = 0; i <= M; i++) {
        if (bitmap_test(bitmap, i)) {
            printf(" %d", i);
        }
    }
    printf("\n");

    free(bitmap);

    return 0;
}
