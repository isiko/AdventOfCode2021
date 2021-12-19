//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.c"

#define inputName "../inputs/14test.txt"
#define inputHeight 16
#define inputLength 4
#define templateLength 4

char template[templateLength+2];
char dictionary[27][27];
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

    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 27; ++j) {
            dictionary[i][j] = '0';
        }
    }

    char line[inputLength+2]; /* or other suitable maximum line size */
    for (int i = 0; i < inputHeight; i++)
    {
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        dictionary[line[0] - 'A'][line[1] - 'A'] = line[3];

        input[i][0] = line[0];
        input[i][1] = line[1];
        output[i] = line[3];
    }
    

    fclose(input_file);
    return (1);
}

bool checkInsertChar(char a, char b){
    assert( a - 'A'>= 0 && b- 'A'>= 0);
//    printf("%c %c -> %c (%d)\n", a, b, dictionary[a - 'A'][b - 'A'], returnValue);
    return dictionary[a - 'A'][b - 'A'] != '0';
}


char getInsertChar(char a, char b){
    assert(checkInsertChar(a,b));
    return dictionary[a - 'A'][b - 'A'];
}

#define startingIndex 1

int main()
{
    if (readFile())
    {
        char* currentResult = template;
        int totalTemplateLength = templateLength;
        for (int i = 0; i < 40; i++)
        {
            int addedLength = 0;
            for (int t = 0; t < totalTemplateLength-1; ++t) {
                if(checkInsertChar(currentResult[t], currentResult[t+1])) {
                    currentResult = insertChar(
                            currentResult,
                            getInsertChar(
                                    currentResult[t+addedLength],
                                    currentResult[t+1+addedLength]
                                ),
                            t+1+addedLength,
                            totalTemplateLength+addedLength);
                    addedLength++;
                }
            }
            totalTemplateLength += addedLength;
            printf("%d: %d\n", i+1, totalTemplateLength);
//            printf("%d: %s\n", i+1, currentResult);
        }

        printf("\n");

        long long int maxQ = -1;
        long long int minQ = -1;
        char* elements = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < 27; ++i) {
            long long int counter = 0;
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
