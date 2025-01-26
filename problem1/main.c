/* @Duren Gouda
 * B00949586
 */

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    float totalSum = 0.0;

    int amount;
    char name[50];
    float unitCost, totalCost;

    for (int i = 0; i < n; i++) {

        scanf("%d %s %f", &amount, name, &unitCost); // input from user

        totalCost = amount * unitCost; // total cost of the product

        totalSum += totalCost; // total bill(sum of all)

        printf("%s : %.2f\n", name, totalCost);
    }

    printf("Total : %.2f\n", totalSum); // Print total

    return 0;
}

