//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define inputLength 1000

int crabs[inputLength];

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

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
    input_file = fopen("../input.txt", "r");

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