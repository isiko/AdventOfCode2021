#include <stdio.h>
#include <stdlib.h>

#define inputLength 200
#define inputHeight 102
char input[inputHeight][inputLength];

int readFile(){
    FILE *input_file;
    input_file = fopen("../../inputs/10.txt", "r");

    if (!input_file){
        printf("Error while loading File");
        return(0);
    }

    for(int i = 0; i<inputHeight; i++){
        char line[inputLength]; /* or other suitable maximum line size */
        fgets(line, sizeof line, input_file);
        line[strcspn(line, "\n")] = 0;
        if(strlen(line) == 0){
            i--;
            continue;
        }
        for(int j = 0; j<inputLength; j++)
            input[i][j] = line[j];
    }

    fclose(input_file);
    return (1);
}

char invertChar(char c){
    switch (c)
    {
        case '(': return ')';
        case ')': return '(';
        case '[': return ']';
        case ']': return '[';
        case '{': return '}';
        case '}': return '{';
        case '<': return '>';
        case '>': return '<';
    }
}

int main() {
    if(readFile()){
        long result = 0;

        //Interate over every Row
        for(int i = 0; i<inputHeight; i++){
            printf("Analysing Row \"%s\"\n", input[i]);
            int rowLength = strlen(input[i]);
            int pos = 0;
            int done = 0;

            char row[inputLength];

            //iterate over every Char
            for (int j = 0; j<rowLength;j++){
                switch(input[i][j]){
                    case '(':
                    case '[':
                    case '{':
                    case '<':
                        row[pos] = input[i][j];
                        pos++;
                        break;
                    case ')':
                    case ']':
                    case '}':
                    case '>':
                        pos--;
                        if(pos<0){
                            done = 1;
                        } else if(row[pos] != invertChar(input[i][j])){
                            switch(input[i][j]){
                                case ')': result+=3; break;
                                case ']': result+=57; break;
                                case '}': result+=1197; break;
                                case '>': result+=25137; break;
                            }
                            printf("Expected '%c', got '%c'\n", row[pos], input[i][j]);
                            done = 1;
                        }
                        break;
                }
                
                if(done == 1) break;
                for(int k = 0; k<=pos; k++) printf("%c", row[k]);
                printf("\n");
            }
        }

        printf("Ergebniss: %d", result);
        return 0;
    }

    return 1;
}