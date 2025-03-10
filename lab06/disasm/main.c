#include <stdio.h>
#include "line.h"
#include "min.h"
#include "max3.h"
#include "sum.h"

int main() {
    printf("Hello, World!\n");
    printf("%d = %d * %d + %d\n", line(3, 4, 5), 3, 4, 5);
    printf("%d = min(%d, %d)\n", min(4, 3), 4, 3);
    printf("%d = max3(%d,%d,%d)\n", max3(4, 3, 5), 4, 3, 5);
    int data[] = {1, 3, 4, 5, 6};
    printf("%d = sum\n", sum(data, 5));
    return 0;
}
