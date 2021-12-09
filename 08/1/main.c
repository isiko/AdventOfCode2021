//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define inputLength 300
#define inputLengthHight 200

char input[10];
char output[4];

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

int main(){
    //Take notes
    FILE *input_file;
    input_file = fopen("../input.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputLength];

    int returnValue = 0;

    for(int i = 0; i<inputLengthHight; i++){
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        char** io = str_split(line, ';');
        char** input = str_split(io[0], ' ');
        char** output = str_split(io[1], ' ');

        for (int j = 0; j < 4; j++){
            printf("\"%s\" %d\n",output[j],strlen(output[j]));

            int length = strlen(output[j]);
            if (length == 2 || length == 4 || length == 3 || length == 7)
            {
                returnValue ++;
            }
        }
    }

    printf("%d\n", returnValue);

    return returnValue;
}