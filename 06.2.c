//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

#define inputFish 5
#define iterationen 256
#define maxCycle 200

unsigned long long fische[9] = { 0 };
unsigned long long lastFisch[9] = { 0 };

int main() {
    FILE *input_file;
    input_file = fopen("../../inputs/06/testInput.txt", "r");
    //input_file = fopen("...txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputFish*2];
    fgets(line, sizeof line, input_file);

    char** input = str_split(line, ',');

    for (int i = 0; i<9;i++)
            fische[i] = 0;

    for(int i = 0; i<inputFish;i++){
        fische[atoi(input[i])]++;

    }

    unsigned int test = 0;
    unsigned int lastTest = 0;
    while (test>= lastTest)
    {
        lastTest = test;
        test += 100000000;
        printf("%d\n", test);
    }
    
    printf("%d", test);

    unsigned long long gesammtFische = inputFish;
    printf("Max %d\n", sizeof(gesammtFische));
    unsigned long long maxFish = gesammtFische;
    for (int i = 0; i < iterationen; i++){
        for (int c = 0; c < 9; c++)
            lastFisch[c] = fische[c];
        for(int c = 8; c>=0; c--){
            switch(c){
                case 8:
                    fische[c] = lastFisch[0];
                    gesammtFische += lastFisch[0];
                    printf("Adding %d Fisch\n", lastFisch[0]);
                    break;
                case 6:
                    fische[c] = lastFisch[0];
                    fische[c] += lastFisch[c+1];
                    break;
                default:
                    fische[c] = lastFisch[c+1];
                    break;
            }
        }

        printf("D %d:\t%d\n", i+1, gesammtFische);
        if(gesammtFische>maxFish) maxFish = gesammtFische;
    }

    printf("Max %d\n",maxFish); 
    printf("Max %d\n", sizeof(fische[0]));
    printf("Max %d\n", sizeof(gesammtFische));

    unsigned long long fishCountTotal = 0;
    for (int fishIndex = 0; fishIndex < 9; fishIndex++)
    {
        fishCountTotal += fische[fishIndex];
    }

    printf("\nCount: %ld\n", fishCountTotal);

    return 0;
}