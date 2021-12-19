//
// Created by isihd on 03.12.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util.c"

#define inputLength 300
#define inputLengthHight 200

char input[10];
char output[4];

int digits[10][7] = {
    {1,1,1,0,1,1,1}, //0
    {0,0,1,0,0,1,0}, //1
    {1,0,1,1,1,0,1}, //2
    {1,0,1,1,0,1,1}, //3
    {0,1,1,1,0,1,0}, //4
    {1,1,0,1,0,1,1}, //5
    {1,1,0,1,1,1,1}, //6
    {1,0,1,0,0,1,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}, //9
};

int isDigit(int testFor[7]){
    for(int i = 0;i<10; i++){
        int success = 1;
        for(int s = 0; s<7; s++)
            if(digits[i][s] != testFor[s]) {
                success = 0;
            }
        if(success == 1){
            return i;
        }
    }
    return -1;
}

int indexFromChar(char c){
    switch(c){
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        default: return -1;
    }
}

int main(){
    //Take notes
    FILE *input_file;
    input_file = fopen("../inputs/08.txt", "r");

    if (!input_file){
        printf("Error while loading File\n");
        return(0);
    }

    char line[inputLength];

    int returnValue = 0;
    int searchedMappings = 0;

    for(int i = 0; i<inputLengthHight; i++){
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        char** io = str_split(line, ';');
        char** input = str_split(io[0], ' ');
        char** output = str_split(io[1], ' ');

        int mappingCorrect = 0;
        int mapping[7] = {-1,-1,-1,-1,-1,-1,-1};

        for(int s0 = 0; s0<7; s0++){
            for(int s1 = 0; s1<7; s1++){
                if(s1 == s0) continue;
                for(int s2 = 0; s2<7; s2++){
                    if(s2 == s0) continue;
                    if(s2 == s1) continue;
                    for(int s3 = 0; s3<7; s3++){
                        if(s3 == s0) continue;
                        if(s3 == s1) continue;
                        if(s3 == s2) continue;
                        for(int s4 = 0; s4<7; s4++){
                            if(s4 == s0) continue;
                            if(s4 == s1) continue;
                            if(s4 == s2) continue;
                            if(s4 == s3) continue;
                            for(int s5 = 0; s5<7;s5++){
                                if(s5 == s0) continue;
                                if(s5 == s1) continue;
                                if(s5 == s2) continue;
                                if(s5 == s3) continue;
                                if(s5 == s4) continue;
                                for(int s6 = 0; s6<7; s6++){
                                    if(s6 == s0) continue;
                                    if(s6 == s1) continue;
                                    if(s6 == s2) continue;
                                    if(s6 == s3) continue;
                                    if(s6 == s4) continue;
                                    if(s6 == s5) continue;

                                    mapping[0] = s0;
                                    mapping[1] = s1;
                                    mapping[2] = s2;
                                    mapping[3] = s3;
                                    mapping[4] = s4;
                                    mapping[5] = s5;
                                    mapping[6] = s6;
                                    searchedMappings++;

                                    int success = 1;
                                    for(int j = 0; j<10;j++){
                                        int currentnumer[7] = {0,0,0,0,0,0,0};
                                        for (int l = 0; l < strlen(input[j]); l++)
                                            currentnumer[mapping[indexFromChar(input[j][l])]] = 1;
                                        if (isDigit(currentnumer) < 0){
                                            success = 0; 
                                            break;
                                        }
                                    }

                                    if(success == 1) mappingCorrect = 1;
                                    if(mappingCorrect == 1) break;
                                }
                                if(mappingCorrect == 1) break;
                            }
                            if(mappingCorrect == 1) break;
                        }
                        if(mappingCorrect == 1) break;
                    }
                    if(mappingCorrect == 1) break;
                }
                if(mappingCorrect == 1) break;
            }
            if(mappingCorrect == 1) break;
        }

        if(mappingCorrect == 1){
            printIntArray("Found Mapping", mapping, 7);
            int multiplyer = 10000;
            int outputValue = 0;
            for (int j = 0; j < 4; j++)
            {
                multiplyer /= 10;
                int currentnumer[7] = {0,0,0,0,0,0,0};
                for (int l = 0; l < strlen(output[j]); l++)
                    currentnumer[mapping[indexFromChar(output[j][l])]] = 1;
                if (isDigit(currentnumer) < 0){
                    printf("Fuck");
                    return 1;
                } else {
                    outputValue += multiplyer*isDigit(currentnumer);
                }
            }
            returnValue += outputValue;
        } else {
            printf("Couldn't find Mapping :/\n");
            return -1;
        }
    }

    printf("Searched %d Mappings\n", searchedMappings);
    printf("%d\n", returnValue);

    return returnValue;
}