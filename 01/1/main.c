//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    int counter = 0;
    int numbers[2000];
    int startingIndex = 1;

    FILE *input;
    input = fopen("../input.txt", "r");

    int i = 0;
    char line[256]; /* or other suitable maximum line size */
    while (fgets(line, sizeof line, input) != NULL){
        numbers[i] = atoi(line);
        i++;
    }

    int lastInt = 0;
    for (int i = startingIndex; i<2000; i++){
        int current = numbers[i];
        printf("%d\n", current);
        if (i != startingIndex && current > lastInt) counter++;
        lastInt = current;
    }
    fclose(input);

    printf("%d Erhoehungen", counter);

    return 0;
}

