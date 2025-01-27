/* @Duren Gouda
* B00949586
 */

#include <stdio.h>
#include <string.h>

int main() {
    char currentWord[29];
    char previousWord[29] = "";

    while (1) {
        scanf("%s", currentWord);


        if (strcmp(currentWord, ".") == 0) { // check for period "."
            break;
        }


        if (strcmp(currentWord, previousWord) != 0) {  // Compares with previous word and print if different
            printf("%s\n", currentWord);
        }


        strcpy(previousWord, currentWord); // Update the previous word
    }

    return 0;
}
