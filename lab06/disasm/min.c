//
// Created by Alex Brodsky on 2023-10-13.
//

#include "min.h"

int min(int a, int b) {
    int m = a;
    if (b < a) {
        m = b;
    }
    return m;
}
