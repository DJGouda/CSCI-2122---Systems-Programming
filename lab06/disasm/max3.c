//
// Created by Alex Brodsky on 2023-10-13.
//

#include "max3.h"

int max3(int a, int b, int c) {
    int result;

    if (a > b && a > c) {
        result = a;
    } else if (b > a && b > c) {
        result = b;
    } else {
        result = c;
    }
    return result;
}