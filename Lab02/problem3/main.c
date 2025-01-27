/* @Duren Gouda
* B00949586
 */

#include <stdio.h>
#include <string.h>

// method for counting words
static void count(const char *word, int *histogram) {
    while (*word) {
        if ('a' <= *word && *word <= 'z') {
            histogram[*word - 'a']++;
        }
        word++;
    }
}

// method to print histogram fro the particular letter
static void printline(const int *histogram, int idx) {
    if (histogram[idx] > 0) {
        printf("%c : ", 'a' + idx);
        for (int i = 0; i < histogram[idx]; i++) {
            printf("*");
        }
        printf("\n");
    }
}

int main() {
    int histogram[26] = {0};
    char currentWord[29];

    while (1) {
        scanf("%s", currentWord);

        if (strcmp(currentWord, ".") == 0) { // check for period "."
            break;
        }
        count(currentWord, histogram); // count letters in the current word
    }

    for (int i = 0; i < 26; i++) { // print histogram
        printline(histogram, i);
    }

    return 0;
}