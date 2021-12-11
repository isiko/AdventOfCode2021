//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "util.c"

int main() {

    int aim = 0;
    int depth = 0;
    int position = 0;

    FILE *input;
    input = fopen("../../inputs/11.txt", "r");
    char line[256]; /* or other suitable maximum line size */

    while (fgets(line, sizeof line, input) != NULL){
        char** splitString = str_split(line, ' ');

        char* command = splitString[0];
        int argument = atoi(splitString[1]);

        if (strcmp(command, "forward") == 0){
            position += argument;
            depth += aim*argument;
        } else if (strcmp(command, "down") == 0){
            aim += argument;
        } else if (strcmp(command, "up") == 0){
            aim -= argument;
        }

        printf("%s\n", splitString[0]);
    }

    printf("%d*%d=%d", depth, position,(depth*position));

    return 0;
}