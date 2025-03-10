//
// Created by Alex Brodsky on 2023-10-13.
//

#include "line.h"

int line(int x, int m, int b) {
    int y;
    y = m * x;
    y = y + b;
    return y;
}
