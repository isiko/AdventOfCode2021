#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.c"

#define inputLength 10
#define inputHeight 10

int input[inputHeight][inputLength];
int flashed[inputHeight][inputLength];
int flashes = 0;

int readFile(){
    FILE *input_file;
    input_file = fopen("../inputs/11.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    char line[(inputLength+1)*inputHeight]; /* or other suitable maximum line size */
    fgets(line, sizeof line, input_file);
    //line[strcspn(line, "\n")] = 0;
    char** inputChars = str_split(line, ';');
    for(int i = 0; i<inputHeight; i++){
        for(int j = 0; j<inputLength; j++){
            input[i][j] = inputChars[i][j] - '0';
            flashed[i][j] = 0;
        }
    }

    // fclose(input_file);
    return (1);
}

void printBoard(){
    printf("\n");
    printf("%d Flashes\n", flashes);
    for (int i = 0; i<inputHeight; i++){
        for (int j = 0; j < inputLength; j++)
        {
            printf("%d", input[i][j]);
        }
        printf("\n");
    }
}

void checkXY(int x, int y, int initalFlash){
    if(initalFlash == 0) input[x][y]++;
    
    if(flashed[x][y] == 0 && input[x][y] > 9){
        
        flashes++;
        flashed[x][y] = 1;
        
        if(x>0) checkXY(x-1, y, 0);
        if(y>0) checkXY(x, y-1, 0);
        if(x<inputHeight-1) checkXY(x+1, y, 0);
        if(y<inputLength-1) checkXY(x, y+1, 0);

        if(y>0 && x>0) checkXY(x-1, y-1, 0);
        if(x<inputHeight-1 && y>0) checkXY(x+1, y-1, 0);
        if(y<inputLength-1 && x>0) checkXY(x-1, y+1, 0);
        if(y<inputLength-1 && x<inputHeight-1) checkXY(x+1, y+1, 0);
    } else {

    }
}

int main(){
    if(readFile()){
        for(int iteration = 0; iteration<100; iteration++){
            // printBoard();
            for (int i = 0; i<inputHeight; i++){
                for (int j = 0; j < inputLength; j++)
                {
                    input[i][j]++;
                }
            }

            for (int i = 0; i<inputHeight; i++){
                for (int j = 0; j < inputLength; j++)
                {
                    if(input[i][j] == 10 && flashed[i][j] == 0) checkXY(i,j, 1);
                }
            }

            for (int i = 0; i<inputHeight; i++){
                for (int j = 0; j < inputLength; j++)
                {
                    if(input[i][j] > 9) input[i][j] = 0;
                    flashed[i][j] = 0;
                }
            }
        }
        printBoard();
    }
}