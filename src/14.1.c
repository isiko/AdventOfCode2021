//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.c"

#define inputName "../inputs/14.txt"
#define inputHeight 100
#define inputLength 4
#define templateLength 20

char template[templateLength+2];
char input[inputHeight][2];
char output[inputHeight];

int readFile()
{
    FILE *input_file;
    input_file = fopen(inputName, "r");

    if (!input_file)
    {
        printf("Error while loading File\n");
        return (0);
    }

    fgets(template, sizeof template, input_file);
    template[strcspn(template, "\n")] = 0;
    printf("Template: \"%s\"\n", template);

    char line[inputLength+2]; /* or other suitable maximum line size */
    for (int i = 0; i < inputHeight; i++)
    {
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        // printf("\"%s\"\n", line);

        input[i][0] = line[0];
        input[i][1] = line[1];
        output[i] = line[3];

//         printf("%c%c -> %c\n", input[i][0], input[i][1], output[i]);
    }
    

    fclose(input_file);
    return (1);
}

bool checkInsertChar(char a, char b){
    for(int ic = 0; ic<inputHeight; ic++){
        if (a == input[ic][0] && b == input[ic][1])
            return true;
    }
    return false;
}

char getInsertChar(char a, char b){
    assert(checkInsertChar(a,b));
    for (int i = 0; i < inputHeight; ++i) {
        if(input[i][0] == a && input[i][1] == b)
            return output[i];
    }
}

#define startingIndex 1

int main()
{
    if (readFile())
    {
        char* currentResult = template;
        int totalTemplateLength = templateLength;
        for (int i = 0; i < 10; i++)
        {
            bool insert[totalTemplateLength];
            memset(insert, false, totalTemplateLength*sizeof(bool));
            for (int c = 0; c < totalTemplateLength; c++)
            {
               insert[c] = checkInsertChar(currentResult[c], currentResult[c+1]);
            }

            int addedLength = 0;
            for (int t = 0; t < totalTemplateLength; ++t) {
                if(insert[t] == true) {
                    currentResult = insertChar(currentResult, getInsertChar(currentResult[t+addedLength], currentResult[t+1+addedLength]), t+1+addedLength, totalTemplateLength+addedLength);
                    addedLength++;
                }
            }
            totalTemplateLength += addedLength;
            printf("%d: %d\n", i, totalTemplateLength);
        }

        int maxQ = -1;
        int minQ = -1;
        char* elements = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < 27; ++i) {
            int counter = 0;
            for(int c = 0; c<totalTemplateLength; c++)
                if(currentResult[c] == elements[i]) counter++;
            if(counter > 0) {
                if (maxQ < counter || maxQ == -1) maxQ = counter;
                if (minQ > counter || minQ == -1) minQ = counter;
                printf("%c: %d\n", elements[i], counter);
            }
        }
        printf("Min: %d\n", minQ);
        printf("Max: %d\n", maxQ);
        printf("Result: %d\n", maxQ - minQ);

        return 0;
    }
    printf("Da is wat Schiefgelaufen");

    return 1;
}
