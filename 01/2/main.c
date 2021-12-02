//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

#define inputLength 2000
int input[inputLength];

int readFile(){
    FILE *input_file;
    input_file = fopen("../input.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    for(int i = 0; i<inputLength; i++){
        char line[256]; /* or other suitable maximum line size */
        if (fgets(line, sizeof line, input_file) != NULL)
            input[i] = atoi(line);
    }

    printf("Test");
    fclose(input_file);
    return (1);
}

int main() {
    if (readFile()) {
        int counter = 0;
        int lastInt = 0;

        for (int i = 2; i < 2000; i++) {
            int sum = input[i] + input[i - 1] + input[i - 2];
            printf("%d\n", sum);
            if (i != 2 && sum > lastInt) counter++;
            lastInt = sum;
        }
        printf("%d Erhoehungen", counter);

        return 0;
    }
}

