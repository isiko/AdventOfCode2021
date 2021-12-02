//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    int counter = 0;
    int numbers[2000];

    FILE *input;
    input = fopen("../input.txt", "r");

    int i = 0;
    char line[256]; /* or other suitable maximum line size */
    while (fgets(line, sizeof line, input) != NULL){
        numbers[i] = atoi(line);
        i++;
    }

    int lastInt = 0;
    for (int i = 2; i<2000; i++){
        int sum = numbers[i] + numbers[i-1] + numbers[i-2];
        printf("%d\n", sum);
        if (i != 2 && sum > lastInt) counter++;
        lastInt = sum;
    }
    fclose(input);

    printf("%d Erhoehungen", counter);

    return 0;
}

