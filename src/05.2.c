//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

#define inputLength 500

int lines[inputLength][2][2];
int map[1000][1000];

void markLinePoints(int start[], int end[]){
    int vel[2];
    for(int i = 0; i<2; i++){
        if(start[i] != end[i])
            if(start[i] < end[i])
                vel[i] = 1;
            else
                vel[i] = -1;
        else
            vel[i] = 0;
    }

    printf("Starting Line at %d:%d\n", start[0], start[1]);
    map[start[0]][start[1]]++;
    while ((start[0] != end[0] || start[1] != end[1])){
        for(int j = 0; j<2; j++)
            start[j] += vel[j];
        map[start[0]][start[1]]++;
        //printf("(%d:%d) -> %d\n", start[0], start[1], map[start[0]][start[1]]);
    }
    printf("Ending Line at %d:%d\n", start[0], start[1]);
}

int main(){
    FILE *input_file;
    input_file = fopen("../inputs/05.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[512];

    for(int x = 0; x<1000; x++){
        for(int y = 0; y<1000; y++){
            map[x][y] = 0;
        }
    }

    for (int i = 0; i < inputLength; i++)
    {
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        char** lineCords = str_split(line, ';');
        char** start = str_split(lineCords[0], ',');
        char** end = str_split(lineCords[1], ',');

        //Start
        lines[i][0][0] = atoi(start[0]);
        lines[i][0][1] = atoi(start[1]);

        //End
        lines[i][1][0] = atoi(end[0]);
        lines[i][1][1] = atoi(end[1]);

        printf("%d:\t%d,%d -> %d,%d\n",i, lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
        markLinePoints(lines[i][0], lines[i][1]);
        printf("\n");
    }

    int result = 0;
    for (int x = 0; x < 1000; x++)
        for (int y = 0; y < 1000; y++)
            if (map[x][y] >= 2)
                result++;
    
    printf("Result: %d", result);

    return 0;
}