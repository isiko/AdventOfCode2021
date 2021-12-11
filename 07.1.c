//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util.c"

#define inputLength 1000

int crabs[inputLength];

int calcDistance(int a, int b) {
    return sqrt((a-b)*(a-b));
}

int calcFuelForPosition(int pos){
    int fuel = 0;

    for (int i = 0; i < inputLength; i++)
        fuel += calcDistance(crabs[i], pos);

    return fuel;
}

int main(){
    //Read Crabs
    FILE *input_file;
    input_file = fopen("../../inputs/07.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputLength*6];
    fgets(line, sizeof line, input_file);
    char** input = str_split(line, ',');

    for (int i = 0; i<inputLength;i++)
        crabs[i] = atoi(input[i]);

    int minCrab = crabs[0];
    int maxCrab = crabs[0];
    for(int i = 0; i<inputLength; i++){
        if(crabs[i]<minCrab) minCrab = crabs[i];
        if(crabs[i]>maxCrab) maxCrab = crabs[i];
    }

    printf("Maximum Crab: %d\n", minCrab);
    printf("Minimum Crab: %d\n", maxCrab);

    int position = minCrab;
    int minFuel = calcFuelForPosition(minCrab);

    for (int i = minCrab; i < maxCrab; i++)
    {
        int fuel=calcFuelForPosition(i);
        if(fuel<minFuel){
            minFuel = fuel;
            position = i;
        }

        printf("%d: \t%d\n", i, fuel);
    }

    //printf("%d\n", calcDistance(16,5));
    
    printf("\n");
    printf("Minimum:\n");
    printf("Position: %d\n", position);
    printf("Fuel: %d\n", minFuel);

    return 0;
}