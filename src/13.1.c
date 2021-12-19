//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.c"

#define inputName "../inputs/13.txt"
#define inputHeight1 802
#define inputLength 2
#define inputSegmentLength 5
bool doPrintDots = false;
int dots[inputHeight1][inputLength];
int folds[2];

int countDots()
{
    int maxY = 0;
    int maxX = 0;
    int counter = 0;

    for (int i = 0; i < inputHeight1; i++)
    {
        maxX = getMax(dots[i][0], maxX);
        maxY = getMax(dots[i][1], maxY);
    }

    for (int y = 0; y <= maxY; y++)
    {
        for (int x = 0; x <= maxX; x++)
        {
            for (int i = 0; i < inputHeight1; i++)
                if (dots[i][0] == x && dots[i][1] == y)
                {
                    counter++;
                    break;
                }
        }
    }
    return counter;
}

void printDots()
{
    if(doPrintDots)
    {
        int maxY = 0;
        int maxX = 0;

        for (int i = 0; i < inputHeight1; i++)
        {
            maxX = getMax(dots[i][0], maxX);
            maxY = getMax(dots[i][1], maxY);
        }

        for (int y = 0; y <= maxY; y++)
        {
            for (int x = 0; x <= maxX; x++)
            {
                bool found = false;
                for (int i = 0; i < inputHeight1; i++)
                    if (dots[i][0] == x && dots[i][1] == y)
                    {
                        printf("#");
                        found = true;
                        break;
                    }
                if (!found)
                    printf(".");
            }
            printf("\n");
        }
    }
}

void foldDim(int s, int d)
{
    printf("Folding along Dimension %d to %d\n", d, s);
    for (int i = 0; i < inputHeight1; i++)
    {
        if (dots[i][d] > s){
            dots[i][d] -= 2 * getDistance(dots[i][d], s);
        }
    }
    printDots();
    printf("There are still %d Dots visible\n", countDots());
}

int readFile()
{
    FILE *input_file;
    input_file = fopen(inputName, "r");

    if (!input_file)
    {
        printf("Error while loading File\n");
        return (0);
    }

    char line[inputLength * (inputSegmentLength + 1) + 1]; /* or other suitable maximum line size */
    for (int h = 0; h < inputHeight1; h++)
    {
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;

        char **currentLine = str_split(line, ',');

        dots[h][0] = atoi(currentLine[0]);
        dots[h][1] = atoi(currentLine[1]);

        printf("%d.\"%d\", \"%d\"\n", h, dots[h][0], dots[h][1]);
    }

    fgets(line, sizeof line, input_file);
    line[strcspn(line, "\n")] = 0;

    char **currentLine = str_split(line, '=');

    if (strcmp("x", currentLine[0])) folds[0] = 1;
    if (strcmp("y", currentLine[0])) folds[0] = 0;

    printf("%s-Axis corresponds to Dimension %d\n", currentLine[0], folds[0]);

    folds[1] = atoi(currentLine[1]);

    fclose(input_file);
    return (1);
}

#define startingIndex 1

int main()
{
    if (readFile())
    {
        printDots();
        foldDim(folds[1], folds[0]);

        return 0;
    }

    printf("Da is wat Schiefgelaufen");

    return 1;
}
