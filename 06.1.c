//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

#define maxFische 0x7ffffff
#define inputFish 300
#define iterationen 80
#define maxCycle 200

int fische[maxCycle];
int lastFisch[maxCycle];

//395627
int main() {
    FILE *input_file;
    //input_file = fopen("../testInput.txt", "r");
    input_file = fopen("../../inputs/06.txt", "r");

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

    int gesammtFische = inputFish;
    for (int i = 0; i < iterationen; i++){
        for (int c = 0; c < 9; c++)
            lastFisch[c] = fische[c];
        for(int c = 8; c>=0; c--){
            switch(c){
                case 8:
                    fische[c] = lastFisch[0];
                    gesammtFische += lastFisch[0];
                    break;
                case 6:
                    fische[c] = lastFisch[0];
                    fische[c] += lastFisch[c+1];
                    break;
                default:
                    fische[c] = lastFisch[c+1];
                    break;
            }
            printf("%d: %d\n", c, lastFisch[c]);
        }
        printf("Tag %d:\t%d\n\n", i+1, gesammtFische);
    }
    

    return 0;
}