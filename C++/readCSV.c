#include "stdio.h"
#include "stdlib.h"

#define MAX_VALUE 999

char* getVariable(char* input, char delim, int* index);
void discard_lines(int n);
char* getALine();

int main(int argc, char* argv[]) {
    discard_lines(1);
    
    int index = 0;
    char* line = getALine();
    printf("%s", line);

    char* number;
    number = getVariable(&line[index], ' ', &index);
    

    number = getVariable(&line[index], ' ', &index);
    printf("%s\n", number);


    //word = getVariable(argv[0], ' ');
    //printf("%s\n", word);
    
    return 0;
}

void discard_lines(int n) {
    int c;
    while ((c=getchar()) != EOF) {
        if (c== '\n') {
            n--;
            if (n==0) return;
        }
    }
    /* Error, as unexpected end of input */
    exit(EXIT_FAILURE); 
}


char* getALine() {
    char* buffer = (char *)malloc(MAX_VALUE * sizeof(char));
    size_t size = MAX_VALUE;
    
    if (!getline(&buffer, &size, stdin))
        return NULL;
    return buffer;
}

char* getVariable(char* input, char delim, int* index) {
    char* currentChar = input;
    char* word  = (char*)malloc(50 * sizeof(char));
    int count = 0;
    while (*currentChar != delim && (*currentChar != EOF && count < 50)) {
        currentChar = input;
        word[count] = *currentChar;
        count++;
        input++;
    }

    index = &count;
    word[count] = '\0';
    return word;
}
