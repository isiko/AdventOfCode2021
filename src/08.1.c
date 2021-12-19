//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util.c"

#define inputLength 300
#define inputLengthHight 200

char input[10];
char output[4];

int main(){
    //Take notes
    FILE *input_file;
    input_file = fopen("../inputs/08.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputLength];

    int returnValue = 0;

    for(int i = 0; i<inputLengthHight; i++){
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        char** io = str_split(line, ';');
        char** input = str_split(io[0], ' ');
        char** output = str_split(io[1], ' ');

        for (int j = 0; j < 4; j++){
            printf("\"%s\" %d\n",output[j], strlen(output[j]));

            int length = strlen(output[j]);
            if (length == 2 || length == 4 || length == 3 || length == 7)
            {
                returnValue ++;
            }
        }
    }

    printf("%d\n", returnValue);

    return returnValue;
}