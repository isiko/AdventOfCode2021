//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

#define inputLength 100
#define inputHeight 100
int map[inputLength][inputHeight];

int readFile(){
    FILE *input_file;
    input_file = fopen("../inputs/09.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    for(int i = 0; i<inputHeight; i++){
        char line[256]; /* or other suitable maximum line size */
        if (fgets(line, sizeof line, input_file) != NULL)
            for(int j = 0; j<inputLength; j++){
                map[j][i] = line[j] - '0';
            }
    }

    fclose(input_file);
    return (1);
}

#define startingIndex 1


//540 low
int main() {
    if(readFile()){
        int totalRisk = 0;
        for(int i = 0; i<inputLength; i++){
            for(int j = 0; j<inputHeight; j++){
                int current = map[i][j];
                if(
                    (i-1< 0 || map[i-1][j]>current) &&
                    (j-1< 0 || map[i][j-1]>current) &&
                    (i+1>=inputLength || map[i+1][j]>current) &&
                    (j+1>=inputHeight || map[i][j+1]>current)
                ) {
                    printf("Found (%d|%d): %d\n", j, i, map[i][j]);
                    totalRisk += current+1;
                }
            }
        }

        printf("%d Erhoehungen", totalRisk);
        return 0;
    }

    return 1;
}

