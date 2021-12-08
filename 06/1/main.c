//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define maxFische 0x7ffffff
#define inputFish 300
#define iterationen 80
#define maxCycle 200

long int fische[maxCycle];
long int lastFisch[maxCycle];

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

//395627
int main() {
    FILE *input_file;
    //input_file = fopen("../testInput.txt", "r");
    input_file = fopen("../input.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputFish*2];
    fgets(line, sizeof line, input_file);

    char** input = str_split(line, ',');

    for (int i = 0; i<9;i++)
            fische[i] = 0;

    for(int i = 0; i<inputFish;i++){
        fische[atoi(input[i])]++;

    }

    int gesammtFische = inputFish;
    for (int i = 0; i < iterationen; i++){
        for (int c = 0; c < 9; c++)
            lastFisch[c] = fische[c];
        for(int c = 8; c>=0; c--){
            switch(c){
                case 8:
                    fische[c] = lastFisch[0];
                    gesammtFische += lastFisch[0];
                    //printf("Adding %d\n", fische[0]);
                    break;
                case 6:
                    fische[c] = lastFisch[0];
                    fische[c] += lastFisch[c+1];
                    break;
                default:
                    fische[c] = lastFisch[c+1];
                    break;
            }
            printf("%d: %d\n", c, lastFisch[c]);
        }
        printf("Tag %d:\t%d\n\n", i+1, gesammtFische);
    }
    

    return 0;
}