//
// Created by Alex Brodsky on 2023-10-13.
//

#include "sum.h"

int sum(int *data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + data[i];
    }
    return sum;
}
