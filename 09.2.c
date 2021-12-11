//
// Created by isihd on 02.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

#define inputLength 100
#define inputHeight 100

int basinValues[246];
int map[inputHeight][inputLength];
int basins[inputHeight][inputLength];

int readFile(){
    FILE *input_file;
    input_file = fopen("../../inputs/09.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    for(int i = 0; i<inputHeight; i++){
        char line[256]; /* or other suitable maximum line size */
        if (fgets(line, sizeof line, input_file) != NULL)
            for(int j = 0; j<inputLength; j++){
                map[i][j] = line[j] - '0';
                basins[i][j] = 0;
            }
    }

    fclose(input_file);
    return (1);
}

int markBasin(int y, int x, int basinIndex){
    int sum = 0;
    if(basins[y][x] == 0 && map[y][x] < 9){
        sum++;
        basins[y][x] = basinIndex;
        if(x>0) sum += markBasin(y,x-1,basinIndex);
        if(y>0) sum += markBasin(y-1,x,basinIndex);
        if(x+1<inputLength) sum += markBasin(y,x+1,basinIndex);
        if(y+1<inputHeight) sum += markBasin(y+1,x,basinIndex);
    } else if (basins[y][x] != 0) {
        //printf("Tryed to Mark basin %d at (%d|%d)\n", basinIndex, y,x);
    }
    return sum;
}

//540 low
int main() {
    if(readFile()){
        int basinCounter = 0;
        for(int i = 0; i<inputHeight; i++){
            for(int j = 0; j<inputLength; j++){
                int current = map[i][j];
                if(
                    (i-1< 0 || map[i-1][j]>current) &&
                    (j-1< 0 || map[i][j-1]>current) &&
                    (i+1>=inputHeight || map[i+1][j]>current) &&
                    (j+1>=inputLength || map[i][j+1]>current)
                ) {
                    basinCounter++;
                    basinValues[basinCounter-1] = markBasin(i, j, basinCounter);
                    printf("Found (%d|%d): %d  \tID: %d\tSize: %d\n", i, j, map[i][j], basinCounter, basinValues[basinCounter-1]);
                }
            }
        }

        int topThree[] = {0,0,0};
        for (int i = 0; i < basinCounter; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(basinValues[i]>topThree[j]){
                    for (int k = j; k < 2; k++)
                    {
                        topThree[k+1] = topThree[k];
                    }
                    
                    topThree[j] = basinValues[i];
                    printf("Neuer %d. höchster Wert bei %d: %d\n", j+1, i, basinValues[i]);
                    break;
                }
            }
        }

        int result = topThree[0]*topThree[1]*topThree[2];
        
        //829080 low
        //847504

        printf("%d\n", result);

        return 0;
    }

    return 1;
}

