//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

#define inputLength 1000
#define inputLength2 12
int zeros[inputLength2];

// Trys
//13717016
int readFile(){
    FILE *input_file;
    input_file = fopen(".../inputs/03.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }
    char line[(inputLength2+1) * inputLength]; /* or other suitable maximum line size */
    fgets(line, sizeof line, input_file);
    char** lines = str_split(line, ' ');
    for (int i = 0; i < inputLength; ++i) {
        for (int j = 0; j < inputLength2; ++j) {
            printf("%c",lines[i][j]);
            if (lines[i][j] == '0')
                zeros[j]++;
        }
        printf("\n");
    }

    fclose(input_file);
    return (1);
}

int main(){
    int gamma = 0;
    int epsilon = 0;
    int gesammt = 0;
    if(readFile()){

        printf("\n");
        int totalZeros = 0;
        for (int i = 0; i < inputLength2 ; i++){
            totalZeros += zeros[i];

            int addition = 1<<(inputLength2-i-1);
            printf("%d ", addition);
            gesammt += addition;
            if (zeros[i] > 500)
                gamma += addition;
            else if (zeros[i] < 500)
                epsilon += addition;
        }

        printf("\n\n%d Gamma\n", gamma);
        printf("%d Epsilon\n", epsilon);
        printf("\n%d Powerconsumption\n", gamma*epsilon);
        printf("\n%d Gesammt\n", gesammt);
        printf("%d Zusammen\n", epsilon + gamma);
        printf("\n%d Nullen\n", totalZeros);
    }
    return 0;
}