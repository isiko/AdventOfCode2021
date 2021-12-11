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

int numbers[inputLength][inputLength2];

int readFile(){
    FILE *input_file;
    input_file = fopen(".../../inputs/03.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }
    char line[(inputLength2+1) * inputLength]; /* or other suitable maximum line size */
    fgets(line, sizeof line, input_file);
    char** lines = str_split(line, ' ');
    for (int i = 0; i < inputLength; ++i) {
        for (int j = 0; j < inputLength2; ++j) {
            if (lines[i][j] == '0') {
                numbers[i][j] = 0;
            }
            else {
                numbers[i][j] = 1;
            }
        }
    }

    fclose(input_file);
    return (1);
}

int getIndex(int higherIsBetter){
    int length = inputLength;
    int removed[inputLength];

    for (int i = 0; i<inputLength;i++)
        removed[i] = 0;

    for (int i = 0; i < inputLength2; ++i) {
        int zero = 0;
        int one = 0;

        //Get most favorable Bit
        for (int j = 0; j < inputLength; ++j) {
            if(removed[j] == 0){
                if (numbers[j][i] == 0) zero++;
                else one++;
            }
        }

        int rightBit = 0;
        if((one>=zero && higherIsBetter == 1) || (one<zero && higherIsBetter == 0)) rightBit = 1;

        for (int j = 0; j < inputLength; ++j) {
            if(removed[j] == 0 && numbers[j][i] != rightBit) {
                removed[j] = 1;
                length--;
            }
        }

        printf("%d Chosen Bit (%d)\n", rightBit, length);
        printf("%d Zeros\n", zero);
        printf("%d Ones\n", one);
        //printf("%d Length\n", length);

        if(length <= 1) break;
    }

    for (int j = 0; j < inputLength; ++j) {
        if(removed[j] == 0) return j;
    }

    return -1;
}

int getDecimalFromIndex(int index){
    int returnValue = 0;
    for (int k = 0; k < inputLength2; k++) {
        int bitValue = numbers[index][k]*(1<<(12-k-1));
        returnValue += bitValue;
        printf("%d", numbers[index][k]);
        //printf("%d ", bitValue);
    }
    return returnValue;
}

// Trys
//7747584 High
//4940598 Low
//40071990
//21553080
//5388270
//5410338
int main(){
    if(readFile()){
        int CO2Scrubber = 0;
        int O2Generator = 0;

        CO2Scrubber = getDecimalFromIndex(getIndex(1));
        printf("\n<<<Found %d>>>\n\n", CO2Scrubber);

        O2Generator = getDecimalFromIndex(getIndex(0));
        printf("\n<<<Found %d>>>\n\n", O2Generator);
        
        printf("%d CO2 Scrubber\n", CO2Scrubber);
        printf("%d O2 Generator\n", O2Generator);
        printf("\n%d Powerconsumption\n", CO2Scrubber*O2Generator);
    }
    return 0;
}