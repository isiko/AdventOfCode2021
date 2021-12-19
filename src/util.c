#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

void printIntArray(char message[], int* array, int length){
    int arrayLen = sizeof(array)/sizeof(array[0]);
    if(strlen(message) > 0) printf("%s: ", message);
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int checkStringForLowerCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'a' && str[i] <= 'z') return 1;
    return 0;
}

int checkStringForUpperCase(char* str){
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'A' && str[i] <= 'Z') return 1;
    return 0;
}

void copyArray(int array1[], int array2[], const int len){
    for(int i = 0; i<len; i++)
        array2[i] = array1[i];
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int getMax(int a, int b){
    if(a>b) return a;
    else return b;
}

int getMin(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int getDistance(int a, int b){
    int d = a-b;
    if(d<0) d = -1*d;
    return d;
}

char* insertChar(char* str, char insert, int pos, int len)
{
    char *result = malloc(len + 1 + 1); // +1 for the null-terminator
    for (int i = 0; i < pos; ++i) {
        result[i] = str[i];
    }
    result[pos] = insert;
    for (int i = pos; i < len; ++i) {
        result[i+1] = str[i];
    }
    result[len+1] = '\0';
//    free(str);
    return &result[0];
}