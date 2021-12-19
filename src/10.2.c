#include <stdio.h>
#include <stdlib.h>

#define inputLength 110
#define inputHeight 102
char input[inputHeight][inputLength];

int readFile(){
    FILE *input_file;
    input_file = fopen("../inputs/10.txt", "r");

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
        default: return ' ';
    }
}

int main() {
    if(readFile()){
        long long int rowScores[inputHeight];
        int incompleteRowAmount = 0;
        for (int i = 0; i < inputHeight; i++)
        {
            rowScores[i] = -1;
        }
        
        //Interate over every Row
        for(int i = 0; i<inputHeight; i++){
            //printf("Analysing Row \"%s\"\n", input[i]);
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
                        pos++;
                        row[pos-1] = input[i][j];
                        break;
                    case ')':
                    case ']':
                    case '}':
                    case '>':
                        pos--;
                        if(pos<0){
                            done = 1;
                        } else if(row[pos] != invertChar(input[i][j])){
                            pos = 0;
                            done = 1;
                        }
                        break;
                }
                
                if(done == 1) break;
            }

            if(pos>0){
                incompleteRowAmount++;
                printf("Completing Row %d: \"%s   ", i, input[i]);
                while (pos>0)
                {
                    pos--;
                    rowScores[i] = rowScores[i] * 5;
                    switch(invertChar(row[pos])){
                        case ')': rowScores[i]+=1; break;
                        case ']': rowScores[i]+=2; break;
                        case '}': rowScores[i]+=3; break;
                        case '>': rowScores[i]+=4; break;
                    }
                    printf("%c", invertChar(row[pos]));
                }
                printf("\"\n");
                printf("Row Score: %lld\n", rowScores[i]);
            }
        }

        int incompleteRows[inputHeight];

        int counter = 0; 
        for(int i = 0; i<inputHeight; i++){
            if(rowScores[i]>-1){
                incompleteRows[counter] = rowScores[i];
                counter++;
            }
        }

        printf("Found %d incomplete Lines\n", incompleteRowAmount);

        for(int i = 0; i<incompleteRowAmount; i++){
            int current = incompleteRows[i];
            int biggerAmount = 0;
            for(int j = 0; j<incompleteRowAmount; j++){
                if(current >= incompleteRows[j]){
                    biggerAmount++;
                }
            }
            if(biggerAmount == ((incompleteRowAmount-1)/2))
                printf("    Middle Score is %d\n", incompleteRows[i]);
            else printf("Middle Score is not %d\n", incompleteRows[i]);
        }

        // To Low 221385334
        return 0;
    }

    return 1;
}