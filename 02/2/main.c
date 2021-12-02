//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

int main() {

    int aim = 0;
    int depth = 0;
    int position = 0;

    FILE *input;
    input = fopen("../input.txt", "r");
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