//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define inputLength 100
#define fieldAmount 100
#define fieldLength 5

int inputs[inputLength];
int fields[fieldAmount][fieldLength][fieldLength];
int fieldMarkings[fieldAmount][fieldLength][fieldLength];

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
    input_file = fopen("../input.txt", "r");

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

    for (int inputIndex = 0; inputIndex < inputLength; inputIndex++){
        for (int f = 0; f < fieldAmount; f++){
            for (int y = 0; y<fieldLength; y++){
                for (int x = 0; x<fieldLength; x++){
                    if (fields[f][y][x] == inputs[inputIndex])
                    {
                        fieldMarkings[f][y][x] = 1;

                        if (checkColum(f, x) == 1 || checkRow(f, y))
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
                            
                            printf("Got Score %d", score);

                            return 0;
                        }
                        
                    }
                }
            }
        }
        
    }
    

    return 0;
}