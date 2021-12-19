//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

#define inputLength 100
#define fieldAmount 100
#define fieldLength 5

int inputs[inputLength];
int fields[fieldAmount][fieldLength][fieldLength];
int fieldMarkings[fieldAmount][fieldLength][fieldLength];

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

int checkColum(int field, int column){
    for (int i = 0; i < fieldLength; i++)
    {
        if (fieldMarkings[field][i][column] == 0) return 0;
    }
    return 1;
}

int checkRow(int field, int row){
    for (int i = 0; i < fieldLength; i++)
    {
        if (fieldMarkings[field][row][i] == 0) return 0;
    }
    return 1;
}

void printBoard(int field){
    for (int y = 0; y < fieldLength; y++)
    {
        for (int x = 0; x < fieldLength; x++)
        {
            printf("%d ", fields[field][y][x]);
        }
        printf("\n");
    }
}

void printBoardMarkings(int field){
    for (int y = 0; y < fieldLength; y++)
    {
        for (int x = 0; x < fieldLength; x++)
        {
            printf("%d ", fieldMarkings[field][y][x]);
        }
        printf("\n");
    }
}

//4176

int main(){
    FILE *input_file;
    input_file = fopen("../inputs/04.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    char line[512];

    fgets(line, sizeof line, input_file);
    char** inputLine = str_split(line, ',');
    for (int i = 0; i < inputLength; i++)
    {
        inputs[i] = atoi(inputLine[i]);
    }

    for (int i = 0; i < fieldAmount; i++)
    {
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        char** field = str_split(line, ';');
        for (int j = 0; j<fieldLength; j++){
            char** field_line = str_split(field[j], ' ');
            for (int k = 0; k < fieldLength; k++)
            {
                // printf("\"%s\" ", field_line[k]);
                fields[i][j][k] = atoi(field_line[k]);
                fieldMarkings[i][j][k] = 0;
            }
        }
    }

    int doneBoard[fieldAmount];
    for (int i = 0; i < fieldAmount; i++)
    {
        doneBoard[i] = 0;
    }

    int boardsDone = 0;
    

    for (int inputIndex = 0; inputIndex < inputLength; inputIndex++){
        for (int f = 0; f < fieldAmount; f++){
            int success = 0;
            for (int y = 0; y<fieldLength; y++){
                for (int x = 0; x<fieldLength; x++){
                    if (fields[f][y][x] == inputs[inputIndex])
                    {
                        fieldMarkings[f][y][x] = 1;

                        if (doneBoard[f] == 0 && (checkColum(f, x) == 1 || checkRow(f, y)))
                        {
                            printBoard(f);
                            printf("\n");
                            printBoardMarkings(f);
                            printf("\nBoard %d won in turn %d with number %d!\n", f, inputIndex, inputs[inputIndex]);
                            
                            //Calculate Score
                            int score = 0;
                            for (int y2 = 0; y2 < fieldLength; y2++){
                                for (int x2 = 0; x2 < fieldLength; x2++){
                                    score += ((fieldMarkings[f][y2][x2]-1)*(-1)) * fields[f][y2][x2];
                                }
                            }

                            score *= inputs[inputIndex];
                            
                            printf("Got Score %d\n", score);

                            doneBoard[f] = 1;
                            boardsDone++;

                            if (boardsDone >= fieldAmount)
                                    return 0;
                        }
                        
                    }
                }
                if (success == 1)
                break;
            }
        }
        
    }
    

    return 0;
}