//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.c"

#define inputHeight 26
#define inputLength 2
#define inputSegmentLength 6

typedef struct cave {
    int size;
    int visited;
    int connections[inputHeight];
    char* name;
} cave;

int ways = 0;
int caveAmount = 0;
cave caves[inputHeight];

void printCaves(char message[]){
    printf("%s: ", message);

    for(int i = 0; i<caveAmount; i++){
        printf("%s, ", caves[i].name);
    }

    printf("\n");
}

int getCave(char* name){
    // printf("Searching for Cave %s, ", name);
    for(int i = 0; i<caveAmount; i++)
        if(!strcmp(caves[i].name, name)){
            // printf("found \"%s\"\n", caves[i].name);
            return i;
        }
    // printf("but didn't Find anything\n");
    return -1;
}

void linkCaves(char* cave1, char* cave2){
    int index1 = getCave(cave1);
    int index2 = getCave(cave2);

    caves[index1].connections[index2] = 1;
    caves[index2].connections[index1] = 1;

    //caves[index1].connections[index1] = 1;
    //caves[index2].connections[index2] = 1;

    printf("Linked %s(%d) and %s(%d)\n", caves[index1].name, index1, caves[index2].name, index2);
}

void addCave(char* pName){
    int size = checkStringForUpperCase(pName);
    int conenctions[inputHeight] = {0};

    // printf("Found Cave \"%s\" with size %d\n", pName, size);

    cave temp = {
        .size = size,
        .visited = 0,
        .connections = *conenctions,
        .name = pName
    };
    caves[caveAmount] = temp;
    caveAmount++;
}

int checkCave(char* name){
    return getCave(name) >-1;
}

void markWay(int markedFields[], int startIndex, char* wayDescription, bool canVisitTwice, bool isFirstNode){
    // printf("Currently at Node \"%s\"\n", caves[startIndex].name);
    if(startIndex == getCave("end")){
        ways++;
        // printf("Found Way Nr %d\n", ways);
        printf("%send\n", wayDescription);
        // printIntArray("Marked Nodes", markedFields, caveAmount);
    } else if(
                (
                    (
                        markedFields[startIndex] == 0 ||
                        canVisitTwice
                    ) ||
                    caves[startIndex].size >0
                ) &&
                (strcmp("start", caves[startIndex].name) || isFirstNode)
            ){
        // printf("Marking Node\n");
        int tempMarkedFields[inputHeight];
        copyArray(markedFields, tempMarkedFields, inputHeight);

        tempMarkedFields[startIndex] = 1;
        
        wayDescription = concat(wayDescription, caves[startIndex].name);
        wayDescription = concat(wayDescription, ", ");

        if(caves[startIndex].size == 0 && markedFields[startIndex] > 0) canVisitTwice = false;

        for (int i = 0; i < caveAmount; i++){
            if(i != startIndex, caves[startIndex].connections[i] == 1) markWay(tempMarkedFields, i, wayDescription, canVisitTwice, false);
        }
    }
}

int readFile(){
    FILE *input_file;
    input_file = fopen("../inputs/12.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    char line[inputLength*inputSegmentLength-1]; /* or other suitable maximum line size */
    for(int h = 0; h<inputHeight; h++){
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;

        char** currentLine = str_split(line, '-');
        if(checkCave(currentLine[0]) == 0) addCave(currentLine[0]);
        if(checkCave(currentLine[1]) == 0) addCave(currentLine[1]);

        linkCaves(currentLine[0], currentLine[1]);
    }

    fclose(input_file);
    return (1);
}

#define startingIndex 1

int main() {

    if(readFile()){
        int startingMarkedFields[inputHeight] = {0};
        markWay(startingMarkedFields, getCave("start"), "", true, true);
        printf("Ways: %d", ways);
        return 0;
    }

    // printf("Da is wat Schiefgelaufen");

    return 1;
}