// @Duren Gouda
// B00949586

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {  // seen example from: https://www.geeksforgeeks.org/how-to-use-typedef-for-struct-in-c/
    int amount;
    char name[20];
    float unitCost;
} Item;

int main() {
    int n;
    scanf("%d", &n);

    Item *items = (Item *)malloc(n * sizeof(Item)); // loading into memory as give in example from lab instructions

    // input
    for (int i = 0; i < n; i++) {
        scanf("%d %s %f", &items[i].amount, items[i].name, &items[i].unitCost);
    }

    // loop through and merge the duplicates with same unitCost
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].amount > 0 && strcmp(items[i].name, items[j].name) == 0 && items[i].unitCost == items[j].unitCost) {
                items[i].amount += items[j].amount;
                items[j].amount = 0;
            }
        }
    }

    // made a counter for all the non zero items
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (items[i].amount > 0) {
            count++;
        }
    }

    // this handles the output
    printf("%d\n", count);
    for (int i = 0; i < n; i++) {
        if (items[i].amount > 0) {
            printf("%d %s %.2f\n", items[i].amount, items[i].name, items[i].unitCost);
        }
    }

    free(items); // usd free in this to deallocate it
    return 0;
}
