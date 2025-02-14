// @ Duren Gouda
// B00949586

#include <stdio.h>
#include <string.h>

char dictionary[20000][29]; // I have taken valeus as per the given rules in the assignment
int wordCount = 0;

// method which will find the panagrams
int countNewLetters(const char *word, char *newLetters) {
    int lCount[26] = {0}, newCount = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'A';
        if (!lCount[index]) {
            lCount[index] = 1;
            newLetters[newCount++] = word[i];
        }
    }
    newLetters[newCount] = '\0';
    return newCount;
}

// this method will give all the letters in alphabetcal order
void sortLetters(char *letters, int length) {
    for (int i = 0; i < length - 1; i++)
        for (int j = i + 1; j < length; j++)
            if (letters[i] > letters[j]) {
                char temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
}

// method that will count the words
int canBeFormed(const char *word, const char *panagramLetters) {
    int lCount[26] = {0};
    for (int i = 0; panagramLetters[i] != '\0'; i++)
        lCount[panagramLetters[i] - 'A'] = 1;

    for (int i = 0; word[i] != '\0'; i++)
        if (!lCount[word[i] - 'A']) return 0;

    return 1;
}

int main() {
    int W;
    scanf("%d", &W);

    for (int i = 0; i < W; i++)
        scanf("%s", dictionary[wordCount++]);

    // here all methods a called accordingly to get the desired ouput
    for (int i = 0; i < wordCount; i++) {
        char newLetters[8];
        if (countNewLetters(dictionary[i], newLetters) == 7) {
            sortLetters(newLetters, 7);

            int count = 0;
            for (int j = 0; j < wordCount; j++)
                if (canBeFormed(dictionary[j], newLetters))
                    count++;

            // this handles all the printing
            printf("%s :", dictionary[i]);
            for (int j = 0; j < 7; j++)
                printf(" %c", newLetters[j]);
            printf(" ; %d\n", count);
        }
    }
    return 0;
}